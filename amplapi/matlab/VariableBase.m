classdef VariableBase < Entity
properties
end
methods
  function obj = VariableBase(impl)
    obj@Entity(impl);
  end

  function result = ub0(self)
    try
      result = self.impl.ub0();
    catch e
       HandleException(e, 'AMPLAPI:Variable:ub0');
    end
  end

  function result = ub2(self)
    try
      result = self.impl.ub2();
    catch e
       HandleException(e, 'AMPLAPI:Variable:ub2');
    end
  end

  function result = ub1(self)
    try
      result = self.impl.ub1();
    catch e
       HandleException(e, 'AMPLAPI:Variable:ub1');
    end
  end

  function result = ub(self)
    try
      result = self.impl.ub();
    catch e
       HandleException(e, 'AMPLAPI:Variable:ub');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:Variable:iterator');
    end
  end

  function result = dual(self)
    try
      result = self.impl.dual();
    catch e
       HandleException(e, 'AMPLAPI:Variable:dual');
    end
  end

  function fix(self,varargin)
    try
      if size(varargin) > 0
        self.impl.fix(varargin);
      else
        self.impl.fix();
      end
    catch e
       HandleException(e, 'AMPLAPI:Variable:fix');
    end
  end

  function result = uslack(self)
    try
      result = self.impl.uslack();
    catch e
       HandleException(e, 'AMPLAPI:Variable:uslack');
    end
  end

  function result = slack(self)
    try
      result = self.impl.slack();
    catch e
       HandleException(e, 'AMPLAPI:Variable:slack');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:Variable:astatus');
    end
  end

  function result = init0(self)
    try
      result = self.impl.init0();
    catch e
       HandleException(e, 'AMPLAPI:Variable:init0');
    end
  end

  function result = lrc(self)
    try
      result = self.impl.lrc();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lrc');
    end
  end

  function result = value(self)
    try
      result = self.impl.value();
    catch e
       HandleException(e, 'AMPLAPI:Variable:value');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:Variable:sstatus');
    end
  end

  function result = init(self)
    try
      result = self.impl.init();
    catch e
       HandleException(e, 'AMPLAPI:Variable:init');
    end
  end

  function result = urc(self)
    try
      result = self.impl.urc();
    catch e
       HandleException(e, 'AMPLAPI:Variable:urc');
    end
  end

  function result = integrality(self)
    try
      result = self.impl.integrality();
    catch e
       HandleException(e, 'AMPLAPI:Variable:integrality');
    end
  end

  function result = rc(self)
    try
      result = self.impl.rc();
    catch e
       HandleException(e, 'AMPLAPI:Variable:rc');
    end
  end

  function result = lb(self)
    try
      result = self.impl.lb();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lb');
    end
  end

  function result = lslack(self)
    try
      result = self.impl.lslack();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lslack');
    end
  end

  function setValue(self,tdouble1)
    try
      self.impl.setValue(tdouble1) ;
    catch e
       HandleException(e, 'AMPLAPI:Variable:setValue');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Variable:equals');
    end
  end

  function unfix(self)
    try
      self.impl.unfix();
    catch e
       HandleException(e, 'AMPLAPI:Variable:unfix');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Variable:toString');
    end
  end

  function result = lb1(self)
    try
      result = self.impl.lb1();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lb1');
    end
  end

  function result = lb0(self)
    try
      result = self.impl.lb0();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lb0');
    end
  end

  function result = lb2(self)
    try
      result = self.impl.lb2();
    catch e
       HandleException(e, 'AMPLAPI:Variable:lb2');
    end
  end

  function result = isScalar(self)
    try
      result = self.impl.isScalar();
    catch e
       HandleException(e, 'AMPLAPI:Variable:isScalar');
    end
  end

  function result = defeqn(self)
    try
      result = self.impl.defeqn();
    catch e
       HandleException(e, 'AMPLAPI:Variable:defeqn');
    end
  end

  function result = status(self)
    try
      result = char(self.impl.status());
    catch e
       HandleException(e, 'AMPLAPI:Variable:status');
    end
  end
end
end
