classdef ParameterBase < Entity
properties
end
methods
  function obj = ParameterBase(impl)
    obj@Entity(impl);
  end

  function result = hasDefault(self)
    try
      result = self.impl.hasDefault();
    catch e
       HandleException(e, 'AMPLAPI:Parameter:hasDefault');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:Parameter:iterator');
    end
  end

  function set(self,varargin)
    try
      if size(varargin) > 0
        self.impl.set(varargin);
      else
        self.impl.set();
      end
    catch e
       HandleException(e, 'AMPLAPI:Parameter:set');
    end
  end

  function setValues(self,varargin)
    try
      if size(varargin) > 0
        self.impl.setValues(varargin);
      else
        self.impl.setValues();
      end
    catch e
       HandleException(e, 'AMPLAPI:Parameter:setValues');
    end
  end

  function result = isSymbolic(self)
    try
      result = self.impl.isSymbolic();
    catch e
       HandleException(e, 'AMPLAPI:Parameter:isSymbolic');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Parameter:equals');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Parameter:toString');
    end
  end

  function result = isScalar(self)
    try
      result = self.impl.isScalar();
    catch e
       HandleException(e, 'AMPLAPI:Parameter:isScalar');
    end
  end
end
end
