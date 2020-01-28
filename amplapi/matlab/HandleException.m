function HandleException( e, methodName )
%HANDLEEXCEPTION Handles exceptions coming from Java
%   Translates java exception into matlab errors
if(isa(e,'matlab.exception.JavaException'))
    ex = e.ExceptionObject;
    if(isa(ex, 'com.ampl.AMPLException'))
        err = MException(methodName, char(ex.toString().replace('\', '/')));
    else
        name = char(ex.getClass().getName());
        name = strrep(name, '.', ':');
        err = MException(name, char(ex.getMessage().replace('\', '/')));
    end
    throw (err)
else
    throw (e)
end
end

