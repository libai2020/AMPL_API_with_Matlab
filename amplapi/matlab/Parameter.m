classdef Parameter < ParameterBase
    
    properties
    end
    
    methods
        function obj = Parameter(impl)
            obj@ParameterBase(impl)
        end
        
        function set(self, varargin)
            if (length(varargin) == 1)
                self.impl.set(varargin{1});
            elseif(length(varargin) == 2)
                self.impl.set(varargin{1}, varargin{2});
            else
                self.impl.set(varargin);
            end
        end
        
        function setValues(self, varargin)
            try
                if(length(varargin) > 2)
                    self.impl.setValues(com.ampl.MatlabUtil.matlabArrayToApiArray(varargin));
                elseif(length(varargin) == 2) %% Normal overload (indices ,values)
                    indices = varargin{1};
                    values = varargin{2};
                    
                    tuples = toTuples(indices, 0);
                    if(iscell(values))
                        self.impl.setValues(tuples,  values);
                    else
                        self.impl.setValues(tuples,  values);
                    end
                    
                    % setValues without indices
                elseif(length(varargin) == 1)
                    input = varargin{1};
                    if( isa(input, 'DataFrame') )
                        self.impl.setValues(input.impl);
                    else
                        if( (length(size(input))==2)  && (size(input, 1) > 1) && (size(input, 2) > 1) )% 2-d assignment
                            self.impl.setValues(input, false);
                        else
                            self.impl.setValues(input);
                        end
                    end
                end
                
            catch e
                if(isa(e,'matlab.exception.JavaException'))
                    ex = e.ExceptionObject;
                    if(isa(ex, 'com.ampl.AMPLException'))
                        err = MException('AMPLAPI:Parameter:setValues', char(ex.toString().replace('\', '/')));
                    else
                        err = MException('AMPLAPI:Parameter:setValues', char(ex.getMessage().replace('\', '/')));
                    end
                    throw (err)
                else
                    throw (e)
                end
            end
        end
        
        function instances = getInstances(self)
            try
                instances = self.impl.getInstances();
                instances = instances.toArray();
                if(self.impl.isSymbolic())
                    instances = cell(instances);
                else
                    temp = zeros(length(instances),1);
                    for i=1:length(instances)
                        temp(i,1) = instances(i);
                    end
                    instances = temp;
                end
                if(isa(e,'matlab.exception.JavaException'))
                    ex = e.ExceptionObject;
                    if(isa(ex, 'com.ampl.AMPLException'))
                        err = MException('AMPLAPI:Parameter:setValues', char(ex.toString().replace('\', '/')));
                    else
                        err = MException('AMPLAPI:Parameter:setValues', char(ex.getMessage().replace('\', '/')));
                    end
                    throw (err)
                else
                    throw (e)
                end
            end
        end
    end
end
