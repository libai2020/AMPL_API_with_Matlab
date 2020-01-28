classdef ObjectiveBase < Entity
properties
end
methods
  function obj = ObjectiveBase(impl)
    obj@Entity(impl);
  end

  function drop(self)
    try
      self.impl.drop();
    catch e
       HandleException(e, 'AMPLAPI:Objective:drop');
    end
  end

  function restore(self)
    try
      self.impl.restore();
    catch e
       HandleException(e, 'AMPLAPI:Objective:restore');
    end
  end

  function result = exitcode(self)
    try
      result = self.impl.exitcode();
    catch e
       HandleException(e, 'AMPLAPI:Objective:exitcode');
    end
  end

  function result = message(self)
    try
      result = char(self.impl.message());
    catch e
       HandleException(e, 'AMPLAPI:Objective:message');
    end
  end

  function result = result(self)
    try
      result = char(self.impl.result());
    catch e
       HandleException(e, 'AMPLAPI:Objective:result');
    end
  end

  function result = iterator(self)
    try
      result = self.impl.iterator();
    catch e
       HandleException(e, 'AMPLAPI:Objective:iterator');
    end
  end

  function result = minimization(self)
    try
      result = self.impl.minimization();
    catch e
       HandleException(e, 'AMPLAPI:Objective:minimization');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:Objective:equals');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:Objective:astatus');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:Objective:toString');
    end
  end

  function result = value(self)
    try
      result = self.impl.value();
    catch e
       HandleException(e, 'AMPLAPI:Objective:value');
    end
  end

  function result = isScalar(self)
    try
      result = self.impl.isScalar();
    catch e
       HandleException(e, 'AMPLAPI:Objective:isScalar');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:Objective:sstatus');
    end
  end
end
end
