classdef Entity < handle
    properties
        impl
    end
    methods(Access = protected)
        function hasReturn = isVoid(self, methodname)
            methodindex = -1;
            methodlist = self.impl.getClass().getMethods();
            for i=1:length(methodlist)
                if(strcmp(methodlist(i).getName(),methodname))
                    methodindex = i;
                    break;
                end
            end
            if(methodindex == -1)
                error('Entity:subsref', 'Method or field not found')
            end
            method = methodlist(methodindex);
            hasReturn = (strcmp(method.getReturnType(), 'void'));
        end
    end
    methods
        function obj = Entity(impl)
            obj.impl = impl;
        end

        function result = subsref(self, key)
            switch key(1).type
                case '()'
                    instance  = self.get(key(1).subs{:});
                    if(isa(instance, 'com.ampl.VariableInstance'))
                        result = VariableInstance(instance);
                    elseif(isa(instance, 'com.ampl.ConstraintInstance'))
                        result  = ConstraintInstance(instance);
                    elseif(isa(instance, 'com.ampl.SetInstance'))
                        result  = SetInstance(instance);
                    elseif(isa(instance, 'com.ampl.ObjectiveInstance'))
                        result  = ObjectiveInstance(instance);
                    else
                        result = instance;
                    end

                    if(length(key) < 2)
                        return
                    end

                    % chain for instance
                    if(strcmp(key(2).subs,'impl'))
                        result = self.impl;
                        return
                    end


                    if(isVoid(self, key(2).subs))
                        subsref(result, key(2:end));
                    else
                        result = subsref(result, key(2:end));
                    end
                    return

                case '.'
                    if(strcmp(key(1).subs,'impl'))
                        result = self.impl;
                        return
                    end
                    methodname = key(1).subs;
                    methodindex = -1;
                    methodlist = self.impl.getClass.getMethods();
                    for i=1:length(methodlist)
                        if(strcmp(methodlist(i).getName(),methodname))
                            methodindex = i;
                            break;
                        end
                    end
                    if(methodindex == -1)
                        error('Entity:subsref', 'Method or field not found')
                    end
                    method = methodlist(methodindex);
                    hasReturn = (strcmp(method.getReturnType(), 'void'));



                    if(hasReturn)
                        builtin('subsref',self,key);
                    else
                        result = builtin('subsref',self,key);
                    end
                    return

                case '{}'
                    error('Entity:subsref', 'Not a supported subscripted reference')

            end
        end


        function display(self)
            % DISPLAY Show a textual representation of this entity
            %   The specifis representation depends on the kind of entity.
            self.impl.toString()
        end

        function instance = get(self, varargin)
            if ((nargin == 1) || (isempty(varargin{1})))
                instance = self.impl.get();
            else
                if(length(varargin) == 1)
                    input = varargin{1};
                    if(length(input)==1)
                        if iscell(input)
                            input = input{1};
                        else
                            input = input(1);
                        end
                    end

                else
                    input = varargin;
                end
                %index = com.ampl.MatlabUtil.matlabArrayToApiArray(input);
                if(length(input) > 1)
                    index = com.ampl.Tuple(input);
                    %toTuples(input, 0);
                else
                    index = input;
                end

                try
                    instance = self.impl.get(index);
                catch e
                    HandleException(e, 'AMPLAPI:Entity:get');
                end

            end

        end


        function data = getValues(self, varargin)
            % GETVALUES Get the values corresponding to the listed suffixes in
            % a DataFrame
            %   Get the values corresponding to the listed suffixes in
            %   a DataFrame. If no suffix is listed, returns the default suffix.
            %   data = getValues('val', 'dual'), if called on a variable,
            %   returns a DataFrame with the primal and dual values for the
            %   variable.
            %   See also DataFrame
            try
                if(nargin > 1)
                    data = DataFrame(-1, self.impl.getValues(varargin));
                else
                    data = DataFrame(-1, self.impl.getValues());
                end
            catch e
                HandleException(e, 'AMPLAPI:Entity:getValues');
            end
        end

        function setValues(self, df)
            try
                self.impl.setValues(df.impl);
            catch e
                HandleException(e, 'AMPLAPI:Entity:setValues');
            end
        end

        function n = numInstances(self)
            n = self.impl.numInstances();
        end

        function list = xref(self)
            % XREF Gets all the entities which are dependent on this
            % Get a list of the entities which depend on this entity
            v = self.impl.xref();
            if(isempty(v))
                list = [];
            else
                list = EntityList(v);
            end
        end

        function indices = getIndices(self)
            % GETINDICES Get the values of indices on which this entity is declared
            % Get all the indices of the current collection
            indices = cell(self.impl.getIndices().toArray());

        end

        function bool = hasIndexing(self)
            % HASINDEXING check whether this entity has indexing or is scalar
            % Returns 1 if the entity has indexing, 0 otherwise
            bool = self.impl.hasIndexing();
        end

        function list = getIndexingSets(self)
            list = cell(self.impl.getIndexingSets());
        end

        function n = indexarity(self)
            % INDEXARITY Get the indexarity of this entity
            % Return the indexarity of this function, defined as the number of
            % items necessary to access an instance of this entity
            n = self.impl.indexarity();
        end

        function n = name(self)
            % NAME Get the name of this entity
            n = char(self.impl.name());
        end

        function size = size(self, varargin)
            size(1) = self.impl.numInstances();
            size(2) = 1;
        end


    end

end
