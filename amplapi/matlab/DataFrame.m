classdef DataFrame < DataFrameBase
    % A DataFrame object stores data in a tabular format, convenient to
    % interact with AMPL
    methods(Access=private)
        function boolean  = isIndex(self, header)
            c=cell(self.impl.getHeaders);
            for i=1:length(c)
                if (strcmp(c{i}, header))
                    index = i;
                    break
                end
            end
            boolean = (index <= self.impl.getNumIndices);
        end

    end
    methods(Static)
        function dataframe = fromTable(nindices, table)
            % Converts a MATLAB table to a DataFrame
            headers= table.Properties.VariableNames;
            dataframe = DataFrame(nindices, headers{:});
            for i = 1:size(headers,2)
                if isa(table.(headers{i}),'double')
                    dataframe.setColumn(headers{i}, num2cell(table.(headers{i})));
                else
                    dataframe.setColumn(headers{i}, table.(headers{i}));
                end
            end
        end
    end
    methods



        function result = subsref(obj,s)
            switch s(1).type
                case '.'
                    isVoid = 1;
                    methodindex = -1;
                    methodname = s(1).subs;
                    if(strcmp(methodname, 'impl'))
                        result = obj.impl;
                        return;
                    end
                    methodlist = obj.impl.getClass.getMethods();
                    for i=1:length(methodlist)
                        method = methodlist(i);
                        if(strcmp(method.getName(),methodname))
                            methodindex = i;
                            isVoid = ~(strcmp(method.getReturnType(), 'void'));
                            break;
                        end
                    end
                    if(methodindex >= 0)
                        if isVoid
                            result =builtin('subsref',obj,s);
                        else
                            builtin('subsref',obj,s);
                        end
                    else
                        if(strcmp(methodname, 'toTable'))
                            result = toTable(obj);
                        else
                            result = obj.getColumn(methodname);
                        end
                    end
                    return;

                case '()'
                    if length(s) == 1
                        if isnumeric(s.subs{1}) % indexing like 1:4
                            result = cell(length(s.subs{1}),1);
                            for i = s.subs{1}
                                result{i,1} = obj.getRowByIndex(i);
                            end
                            return;
                        else
                            result = obj.getRow(s.subs{:});
                        end
                    else
                        % Use built-in for any other expression
                        result = {builtin('subsref',obj,s)};
                    end
                otherwise
                    error('Not a valid indexing expression for DataFrames')

            end
        end

        function t= toTable(self)
            % Convert this dataframe to a MATLAB table,
            % using the headers as variable names
            t = table;
            h = self.getHeaders();
            for i=1:length(h)
                t.(strrep(char(h(i)), '.', '_')) = self.getColumn(h(i));
            end

        end

        function obj = DataFrame(varargin)
            % Constructor; constructs a DataFrame Object
            % Two possibilities:
            % DataFrame(nindices, index1, ..., indexn) where index1..indexn are
            % the names of the n indexing  columns
            % or
            % DataFrame(entity1, ..., entityn) where entity1...entityn are AMPL
            % entities
            if(nargin > 1)
                if(varargin{1} == -1)
                    s=varargin{2};
                else
                    if(isa(varargin{1}, 'Entity'))
                        fff  = toJava('com.ampl.Entity', varargin{1:end});
                        s = com.ampl.DataFrame(fff);
                    else
                        fff  = toJava('java.lang.String', varargin{2:end});
                        s = com.ampl.DataFrame(varargin{1}, fff);
                    end
                end
            else
                s = com.ampl.DataFrame(varargin{:});
            end

            obj@DataFrameBase(s)
        end

        function display(self)
            % DISPLAY Show a textual representation of this entity
            % The specifis representation depends on the kind of entity.
            self.impl.toString()
        end

        function r = eq(obj1,obj2)
            r = obj1.impl.equals(obj2.impl);
        end

        function addColumn(self, header, values)
            % ADDCOLUMN add a column to this dataframe with the specified
            % header and values
            switch nargin
                case 2
                    self.impl.addColumn(header);
                case 3
                    if(self.impl.getNumCols < self.impl.getNumIndices)
                        v = com.ampl.MatlabUtil.matlabArrayToIndices(values);
                    else
                        if(iscell(values))
                            v = com.ampl.MatlabUtil.matlabArrayToApiArray(values);
                        else
                            v = values;
                        end
                    end
                    self.impl.addColumn(header, v);
                otherwise error('error');
            end
        end

        function setColumn(self, header, values)
            % SETCOLUMN set the values for a column
            if(self.isIndex(header))
                v = com.ampl.MatlabUtil.matlabArrayToIndices(values);
            else
                if(iscell(values))
                    v = com.ampl.MatlabUtil.matlabArrayToApiArray(values);
                else
                    v = values;
                end
            end

            self.impl.setColumn(header, v);
        end

        function setMatrix(self, values, varargin)
            % SETMATRIX set the values of a matrix to this DataFrame.
            % The semantic is:
            % setMatrix(values, index1, ..., indexn), where values is an n-dimensional matrix and index1...indexn
            % are the name of the indexing column corresponding to each
            % dimension of the matrix
            self.impl.setMatrixPacked(values, varargin);
        end


        function sizes = size(self, varargin)
            r = self.impl.getNumRows();
            c = self.impl.getNumCols();
            sizes(1) = r;
            sizes(2) = c;
        end


        function row = getRowByIndex(self, index)
            row = cell(self.impl.getRowByIndex(index -1));
        end

        function result = getColumnAsStrings(self,header)
            result = cell(getColumnAsStrings@DataFrameBase(self, header));
        end
        function result = getColumn(self,header)
            result = cell(getColumn@DataFrameBase(self, header));
        end
        function result = getRow(self,varargin)
            result = cell(getRow@DataFrameBase(self, varargin{1:end}));
        end


    end
end
