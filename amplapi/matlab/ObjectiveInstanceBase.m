classdef ObjectiveInstanceBase < Instance
properties
end
methods
  function obj = ObjectiveInstanceBase(impl)
    obj@Instance(impl);
  end

  function drop(self)
    try
      self.impl.drop();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:drop');
    end
  end

  function restore(self)
    try
      self.impl.restore();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:restore');
    end
  end

  function result = exitcode(self)
    try
      result = self.impl.exitcode();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:exitcode');
    end
  end

  function result = message(self)
    try
      result = char(self.impl.message());
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:message');
    end
  end

  function delete(self)
    try
      self.impl.delete();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:delete');
    end
  end

  function result = result(self)
    try
      result = char(self.impl.result());
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:result');
    end
  end

  function result = minimization(self)
    try
      result = self.impl.minimization();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:minimization');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:equals');
    end
  end

  function result = astatus(self)
    try
      result = char(self.impl.astatus());
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:astatus');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:toString');
    end
  end

  function result = value(self)
    try
      result = self.impl.value();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:value');
    end
  end

  function result = key(self)
    try
      result = self.impl.key();
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:key');
    end
  end

  function result = sstatus(self)
    try
      result = char(self.impl.sstatus());
    catch e
       HandleException(e, 'AMPLAPI:ObjectiveInstance:sstatus');
    end
  end
end
end
