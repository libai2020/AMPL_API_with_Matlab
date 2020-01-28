classdef ConstraintBase < Entity
properties
end
methods
  function obj = ConstraintBase(impl)
    obj@Entity(impl);
  end

  function drop(self)
    try
      self.impl.drop();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:drop');
    end
  end

  function result = dinit(self)
    try
      result = self.impl.dinit();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:dinit');
    end
  end

  function result = ubs(self)
    try
      result = self.impl.ubs();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:ubs');
    end
  end

  function result = ldual(self)
    try
      result = self.impl.ldual();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:ldual');
    end
  end

  function result = body(self)
    try
      result = self.impl.body();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:body');
    end
  end

  function result = ub(self)
    try
      result = self.impl.ub();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:ub');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:iterator');
    end
  end

  function result = dual(self)
    try
      result = self.impl.dual();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:dual');
    end
  end

  function result = uslack(self)
    try
      result = self.impl.uslack();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:uslack');
    end
  end

  function result = slack(self)
    try
      result = self.impl.slack();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:slack');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:Constraint:astatus');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:Constraint:sstatus');
    end
  end

  function result = val(self)
    try
      result = self.impl.val();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:val');
    end
  end

  function result = dinit0(self)
    try
      result = self.impl.dinit0();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:dinit0');
    end
  end

  function restore(self)
    try
      self.impl.restore();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:restore');
    end
  end

  function result = defvar(self)
    try
      result = self.impl.defvar();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:defvar');
    end
  end

  function result = isLogical(self)
    try
      result = self.impl.isLogical();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:isLogical');
    end
  end

  function result = udual(self)
    try
      result = self.impl.udual();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:udual');
    end
  end

  function result = lb(self)
    try
      result = self.impl.lb();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:lb');
    end
  end

  function result = lslack(self)
    try
      result = self.impl.lslack();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:lslack');
    end
  end

  function setDual(self,tdouble1)
    try
      self.impl.setDual(tdouble1) ;
    catch e
       HandleException(e, 'AMPLAPI:Constraint:setDual');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Constraint:equals');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Constraint:toString');
    end
  end

  function result = lbs(self)
    try
      result = self.impl.lbs();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:lbs');
    end
  end

  function result = isScalar(self)
    try
      result = self.impl.isScalar();
    catch e
       HandleException(e, 'AMPLAPI:Constraint:isScalar');
    end
  end

  function result = status(self)
    try
      result = char(self.impl.status());
    catch e
       HandleException(e, 'AMPLAPI:Constraint:status');
    end
  end
end
end
