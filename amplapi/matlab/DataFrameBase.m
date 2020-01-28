classdef DataFrameBase < handle
properties
  impl
end
methods
  function obj = DataFrameBase(impl)
    obj.impl = impl;
  end

  function result = getColumnAsDoubles(self,tObject1)
    try
      result = self.impl.getColumnAsDoubles(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getColumnAsDoubles');
    end
  end

  function result = getNumRows(self)
    try
      result = self.impl.getNumRows();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getNumRows');
    end
  end

  function addColumn(self,varargin)
    try
      if size(varargin) > 0
        self.impl.addColumn(varargin);
      else
        self.impl.addColumn();
      end
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:addColumn');
    end
  end

  function result = getNumCols(self)
    try
      result = self.impl.getNumCols();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getNumCols');
    end
  end

  function result = getHeaders(self)
    try
      result = self.impl.getHeaders();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getHeaders');
    end
  end

  function result = getColumnAsStrings(self,tObject1)
    try
      result = self.impl.getColumnAsStrings(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getColumnAsStrings');
    end
  end

  function result = getRow(self,varargin)
    try
      if size(varargin) > 0
        result = self.impl.getRow(varargin);
      else
        result = self.impl.getRow();
      end
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getRow');
    end
  end

  function addRow(self,varargin)
    try
      if size(varargin) > 0
        self.impl.addRow(varargin);
      else
        self.impl.addRow();
      end
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:addRow');
    end
  end

  function result = getRowByIndex(self,tint1)
    try
      result = self.impl.getRowByIndex(tint1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getRowByIndex');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:iterator');
    end
  end

  function result = getNumIndices(self)
    try
      result = self.impl.getNumIndices();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getNumIndices');
    end
  end

  function setColumn(self,param0,param1)
    try
      self.impl.setColumn(param0, param1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:setColumn');
    end
  end

  function result = hashCode(self)
    try
      result = self.impl.hashCode();
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:hashCode');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:equals');
    end
  end

  function setValue(self,varargin)
    try
      if size(varargin) > 0
        self.impl.setValue(varargin);
      else
        self.impl.setValue();
      end
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:setValue');
    end
  end

  function result = getColumn(self,tObject1)
    try
      result = self.impl.getColumn(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:getColumn');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:toString');
    end
  end

  function setMatrix(self,varargin)
    try
      if size(varargin) > 0
        self.impl.setMatrix(varargin);
      else
        self.impl.setMatrix();
      end
    catch e
       HandleException(e, 'AMPLAPI:DataFrame:setMatrix');
    end
  end
end
end
