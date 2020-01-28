classdef SetBase < Entity
properties
end
methods
  function obj = SetBase(impl)
    obj@Entity(impl);
  end

  function result = containsAll(self,param0)
    try
      result = self.impl.containsAll(param0) ;
    catch e
       HandleException(e, 'AMPLAPI:Set:containsAll');
    end
  end

  function result = isEmpty(self)
    try
      result = self.impl.isEmpty();
    catch e
       HandleException(e, 'AMPLAPI:Set:isEmpty');
    end
  end

  function result = arity(self)
    try
      result = self.impl.arity();
    catch e
       HandleException(e, 'AMPLAPI:Set:arity');
    end
  end

  function result = toSet(self)
    try
      result = self.impl.toSet();
    catch e
       HandleException(e, 'AMPLAPI:Set:toSet');
    end
  end

  function result = contains(self,tObject1)
    try
      result = self.impl.contains(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Set:contains');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:Set:iterator');
    end
  end

  function result = size(self)
    try
      result = self.impl.size();
    catch e
       HandleException(e, 'AMPLAPI:Set:size');
    end
  end

  function setValues(self,param0)
    try
      self.impl.setValues(param0) ;
    catch e
       HandleException(e, 'AMPLAPI:Set:setValues');
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
       HandleException(e, 'AMPLAPI:Set:setValuesFlattened');
    end
  end

  function result = members(self)
    try
      result = self.impl.members();
    catch e
       HandleException(e, 'AMPLAPI:Set:members');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Set:equals');
    end
  end

  function result = toArray(self)
    try
      result = self.impl.toArray();
    catch e
       HandleException(e, 'AMPLAPI:Set:toArray');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Set:toString');
    end
  end

  function result = isScalar(self)
    try
      result = self.impl.isScalar();
    catch e
       HandleException(e, 'AMPLAPI:Set:isScalar');
    end
  end
end
end
