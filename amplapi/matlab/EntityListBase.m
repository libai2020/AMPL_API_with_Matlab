classdef EntityListBase < handle
properties
  impl
end
methods
  function obj = EntityListBase(impl)
    obj.impl = impl;
  end

  function result = lastIndexOf(self,tObject1)
    try
      result = self.impl.lastIndexOf(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:EntityList:lastIndexOf');
    end
  end

  function result = contains(self,tObject1)
    try
      result = self.impl.contains(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:EntityList:contains');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:EntityList:iterator');
    end
  end

  function result = size(self)
    try
      result = self.impl.size();
    catch e
       HandleException(e, 'AMPLAPI:EntityList:size');
    end
  end

  function result = containsAll(self,tCollection1)
    try
      result = self.impl.containsAll(tCollection1) ;
    catch e
       HandleException(e, 'AMPLAPI:EntityList:containsAll');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:EntityList:equals');
    end
  end

  function result = isEmpty(self)
    try
      result = self.impl.isEmpty();
    catch e
       HandleException(e, 'AMPLAPI:EntityList:isEmpty');
    end
  end

  function result = toArray(self,varargin)
    try
      if size(varargin) > 0
        result = self.impl.toArray(varargin);
      else
        result = self.impl.toArray();
      end
    catch e
       HandleException(e, 'AMPLAPI:EntityList:toArray');
    end
  end

  function result = listIterator(self,varargin)
    try
      if size(varargin) > 0
        result = self.impl.listIterator(varargin);
      else
        result = self.impl.listIterator();
      end
    catch e
       HandleException(e, 'AMPLAPI:EntityList:listIterator');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:EntityList:toString');
    end
  end

  function result = indexOf(self,tObject1)
    try
      result = self.impl.indexOf(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:EntityList:indexOf');
    end
  end
end
end
