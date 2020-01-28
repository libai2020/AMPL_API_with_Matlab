classdef Set < SetBase
    properties
    end
    
    methods
        function obj = Set(impl)
            obj@SetBase(impl)
        end
      
        
        function setValues(self,varargin)
            % SETVALUES Sets the values of this set members. Applicable only
            % for non-indexed sets.
            % For simple sets, pass a cell array or a vector with all the
            % elements in the set.
            % For sets of tuples:
            % set A dimen 2;
            % 1. Pass tuples: setValues{Tuple(4,5), Tuple('5',6))
            % 2. Pass cell arrays: setValues({{4,5}, {'5', 6}});
            % 3. Pass matrices setValues([4,5 ; 4 6]);
            % Or pass a DataFrame to assign the indexing columns values to
            % the set
            try
                if(length(varargin) == 1)
                    input = varargin{1};
                    if(isa(input,'DataFrame'))
                        self.impl.setValues(input.impl);
                    else
                        self.impl.setValues(toTuples(input,0));
                    end
                else % sequential, each item in varargin is a tuple or an element
                    %             nTuples = length(varargin)
                    input = toTuples(varargin, 1);
                    self.impl.setValues(input);
                end
            catch e
                HandleException(e, 'AMPLAPI:Set:setValues');
            end
        end
        
        function setinstance = get(self, varargin)
            g = get@Entity(self, varargin);
            setinstance = SetInstance(g);
        end
        
        function result = contains(self,tObject1)
            try
                if(isa(tObject1, 'Tuple'))
                    result = contains@SetBase(self, tObject1.impl);
                else
                    result = self.impl.contains(tObject1);
                end
            catch e
                HandleException(e, 'AMPLAPI:Set:contains');
            end
        end
    end
end