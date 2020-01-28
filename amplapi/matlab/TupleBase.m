classdef TupleBase < handle
properties
  impl
end
methods
  function obj = TupleBase(impl)
    obj.impl = impl;
  end

  function result = size(self)
    try
      result = self.impl.size();
    catch e
       HandleException(e, 'AMPLAPI:Tuple:size');
    end
  end

  function result = hashCode(self)
    try
      result = self.impl.hashCode();
    catch e
       HandleException(e, 'AMPLAPI:Tuple:hashCode');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Tuple:equals');
    end
  end

  function result = elements(self)
    try
      result = self.impl.elements();
    catch e
       HandleException(e, 'AMPLAPI:Tuple:elements');
    end
  end

  function result = clone(self)
    try
      result = self.impl.clone();
    catch e
       HandleException(e, 'AMPLAPI:Tuple:clone');
    end
  end

  function insert(self,array1,tint2)
    try
      self.impl.insert(array1, tint2) ;
    catch e
       HandleException(e, 'AMPLAPI:Tuple:insert');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Tuple:toString');
    end
  end

  function result = subtuple(self,tint1,tint2)
    try
      result = self.impl.subtuple(tint1, tint2) ;
    catch e
       HandleException(e, 'AMPLAPI:Tuple:subtuple');
    end
  end
end
end
