classdef VariableInstanceBase < Instance
properties
end
methods
  function obj = VariableInstanceBase(impl)
    obj@Instance(impl);
  end

  function result = ub0(self)
    try
      result = self.impl.ub0();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:ub0');
    end
  end

  function result = ub2(self)
    try
      result = self.impl.ub2();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:ub2');
    end
  end

  function result = ub1(self)
    try
      result = self.impl.ub1();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:ub1');
    end
  end

  function delete(self)
    try
      self.impl.delete();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:delete');
    end
  end

  function result = ub(self)
    try
      result = self.impl.ub();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:ub');
    end
  end

  function result = dual(self)
    try
      result = self.impl.dual();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:dual');
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
       HandleException(e, 'AMPLAPI:VariableInstance:fix');
    end
  end

  function result = uslack(self)
    try
      result = self.impl.uslack();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:uslack');
    end
  end

  function result = slack(self)
    try
      result = self.impl.slack();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:slack');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:astatus');
    end
  end

  function result = init0(self)
    try
      result = self.impl.init0();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:init0');
    end
  end

  function result = lrc(self)
    try
      result = self.impl.lrc();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lrc');
    end
  end

  function result = value(self)
    try
      result = self.impl.value();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:value');
    end
  end

  function result = key(self)
    try
      result = self.impl.key();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:key');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:sstatus');
    end
  end

  function result = init(self)
    try
      result = self.impl.init();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:init');
    end
  end

  function result = urc(self)
    try
      result = self.impl.urc();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:urc');
    end
  end

  function result = rc(self)
    try
      result = self.impl.rc();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:rc');
    end
  end

  function result = lb(self)
    try
      result = self.impl.lb();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lb');
    end
  end

  function result = lslack(self)
    try
      result = self.impl.lslack();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lslack');
    end
  end

  function setValue(self,tdouble1)
    try
      self.impl.setValue(tdouble1) ;
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:setValue');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:equals');
    end
  end

  function unfix(self)
    try
      self.impl.unfix();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:unfix');
    end
  end

  function result = lb1(self)
    try
      result = self.impl.lb1();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lb1');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:toString');
    end
  end

  function result = lb0(self)
    try
      result = self.impl.lb0();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lb0');
    end
  end

  function result = lb2(self)
    try
      result = self.impl.lb2();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:lb2');
    end
  end

  function result = defeqn(self)
    try
      result = self.impl.defeqn();
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:defeqn');
    end
  end

  function result = status(self)
    try
      result = char(self.impl.status());
    catch e
       HandleException(e, 'AMPLAPI:VariableInstance:status');
    end
  end
end
end
