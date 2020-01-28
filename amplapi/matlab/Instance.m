classdef Instance < handle
properties
  impl
end
methods
  function obj = Instance(impl)
    obj.impl = impl;
    end



  function result = entity(self)
    try
      result = self.impl.entity();
      if (isa(self, 'ConstraintInstance'))
          result = Constraint(result);
      elseif (isa(self, 'ObjectiveInstance'))
          result = Objective(result);
      elseif (isa(self, 'VariableInstance'))
          result = Variable(result);
      elseif (isa(self, 'SetInstance'))
          result = Set(result);
      end

    catch e
      if(isa(e,'matlab.exception.JavaException'))
        ex = e.ExceptionObject;
        if(isa(ex, 'com.ampl.AMPLException'))
          err = MException('AMPLAPI:Instance:entity', char(ex.toString().replace('\', '/')));
        else
          err = MException('AMPLAPI:Instance:entity', char(ex.getMessage().replace('\', '/')));
        end
        throw (err)
      else
        throw (e)
      end
    end
    end

    function display(self)
        disp(self.impl.toString());
    end

end
end
