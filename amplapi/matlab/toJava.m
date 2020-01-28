function javaObjectArray = toJava(type, varargin )
%TOJAVA Converts the input arguments to a java Object[]
%   type = java.lang.Object:
%   Converts all the argument in the varargin to an array of java objects,
%   converting the native char to java.lang.String, the native double to
%   java.lang.Double, the Entities to the corresponding com.ampl.Entity
%   type = com.ampl.Entity
%   Converts all the argument inheriting from Entity to their inner reference

nVar = length(varargin);

javaObjectArray = javaArray(type, nVar);
if(strcmp(type,'java.lang.Object'))
    for i = 1:nVar
        if(isa(varargin{i}, 'Entity'))
            javaObjectArray(i)=varargin{i}.impl;
        else
            if(isa(varargin{i}, 'char'))
                javaObjectArray(i)= javaObject('java.lang.String', varargin{i});
            else
                if(isa(varargin{i}, 'double'))
                    javaObjectArray(i)= javaObject('java.lang.Double', varargin{i});
                else
                    javaObjectArray(i)=varargin{i};
                end
            end
        end
    end
else
    if(strcmp(type,'com.ampl.Entity'))
        for i = 1:nVar
            if(isa(varargin{i}, 'Entity'))
                javaObjectArray(i)=varargin{i}.impl;
            else
                error(sprintf('%s %d %s','Argument',varargin{i}, 'is not supported'))
            end
        end
        
    else if(strcmp(type,'java.lang.String'))
            for i = 1:nVar
                if(isa(varargin{i}, 'char'))
                    javaObjectArray(i)= javaObject('java.lang.String', varargin{i});
                else
                    error(sprintf('%s %d %s', 'Argument', i, 'is not supported'))
                end
            end
            
        end
    end
end


end

