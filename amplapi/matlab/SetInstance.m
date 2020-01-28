classdef SetInstance < SetInstanceBase
    %SETINSTANCE Represent a set instance
    %   A set instance
    
    properties
    end
    
    methods
        function obj = SetInstance(impl)
            obj@SetInstanceBase(impl)
        end
        
        function display(self)
            self.impl.toString()
        end
        
        function setValues(self,varargin)
            % SETVALUES Sets the values of this set members. Applicable only
            % for non-indexed sets.
            % For simple sets, pass a cell array or a vector with all the
            % elements in the set.
            % For sets of tuples:
            % set A dimen 2;
            % 1. Pass tuples: setValues(Tuple(4,5), Tuple('5',6))
            % 2. Pass cell arrays: setValues({4,5}, {'5', 6});
            % 3. Pass matrices setValues([4,5 ; 4 6]);
            if(length(varargin) == 1)
                input = varargin{1};
                %             nTuples = size(input, 1)
                %             arity = size(input ,2)
                self.impl.setValues(toTuples(input,0));
            else % sequential, each item in varargin is a tuple or an element
                %             nTuples = length(varargin)
                input = toTuples(varargin, 1);
                self.impl.setValues(input);
            end
        end
        
        function arr = toArray(self)
            arr = self.impl.toArray();
            arr = cell(arr);
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
                HandleException(e, 'AMPLAPI:SetInstance:getValues');
            end
        end
        
    end
    
    
end

