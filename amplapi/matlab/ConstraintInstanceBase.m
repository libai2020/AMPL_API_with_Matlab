classdef ConstraintInstanceBase < Instance
properties
end
methods
  function obj = ConstraintInstanceBase(impl)
    obj@Instance(impl);
  end

  function drop(self)
    try
      self.impl.drop();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:drop');
    end
  end

  function result = dinit(self)
    try
      result = self.impl.dinit();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:dinit');
    end
  end

  function result = ubs(self)
    try
      result = self.impl.ubs();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:ubs');
    end
  end

  function result = ldual(self)
    try
      result = self.impl.ldual();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:ldual');
    end
  end

  function result = body(self)
    try
      result = self.impl.body();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:body');
    end
  end

  function delete(self)
    try
      self.impl.delete();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:delete');
    end
  end

  function result = ub(self)
    try
      result = self.impl.ub();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:ub');
    end
  end

  function result = dual(self)
    try
      result = self.impl.dual();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:dual');
    end
  end

  function result = uslack(self)
    try
      result = self.impl.uslack();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:uslack');
    end
  end

  function result = slack(self)
    try
      result = self.impl.slack();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:slack');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:astatus');
    end
  end

  function result = key(self)
    try
      result = self.impl.key();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:key');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:sstatus');
    end
  end

  function result = val(self)
    try
      result = self.impl.val();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:val');
    end
  end

  function result = dinit0(self)
    try
      result = self.impl.dinit0();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:dinit0');
    end
  end

  function restore(self)
    try
      self.impl.restore();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:restore');
    end
  end

  function result = defvar(self)
    try
      result = self.impl.defvar();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:defvar');
    end
  end

  function result = udual(self)
    try
      result = self.impl.udual();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:udual');
    end
  end

  function result = lb(self)
    try
      result = self.impl.lb();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:lb');
    end
  end

  function result = lslack(self)
    try
      result = self.impl.lslack();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:lslack');
    end
  end

  function setDual(self,tdouble1)
    try
      self.impl.setDual(tdouble1) ;
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:setDual');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:equals');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:toString');
    end
  end

  function result = lbs(self)
    try
      result = self.impl.lbs();
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:lbs');
    end
  end

  function result = status(self)
    try
      result = char(self.impl.status());
    catch e
       HandleException(e, 'AMPLAPI:ConstraintInstance:status');
    end
  end
end
end
