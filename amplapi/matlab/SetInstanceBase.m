classdef SetInstanceBase < Instance
properties
end
methods
  function obj = SetInstanceBase(impl)
    obj@Instance(impl);
  end

  function result = toSet(self)
    try
      result = self.impl.toSet();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:toSet');
    end
  end

  function result = contains(self,tObject1)
    try
      result = self.impl.contains(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:contains');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:iterator');
    end
  end

  function result = size(self)
    try
      result = self.impl.size();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:size');
    end
  end

  function setValues(self,param0)
    try
      self.impl.setValues(param0) ;
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:setValues');
    end
  end

  function setValuesFlattened(self,varargin)
    try
      if size(varargin) > 0
        self.impl.setValuesFlattened(varargin);
      else
        self.impl.setValuesFlattened();
      end
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:setValuesFlattened');
    end
  end

  function result = containsAll(self,param0)
    try
      result = self.impl.containsAll(param0) ;
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:containsAll');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:equals');
    end
  end

  function result = toArray(self)
    try
      result = self.impl.toArray();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:toArray');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:toString');
    end
  end

  function delete(self)
    try
      self.impl.delete();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:delete');
    end
  end

  function result = key(self)
    try
      result = self.impl.key();
    catch e
       HandleException(e, 'AMPLAPI:SetInstance:key');
    end
  end
end
end
