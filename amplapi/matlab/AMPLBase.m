classdef AMPLBase < handle
properties
  impl
end
methods
  function obj = AMPLBase(impl)
    obj.impl = impl;
  end

  function setDblOption(self,tString1,tdouble2)
    try
      self.impl.setDblOption(tString1, tdouble2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setDblOption');
    end
  end

  function result = getSets(self)
    try
      result = self.impl.getSets();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getSets');
    end
  end

  function result = getVariables(self)
    try
      result = self.impl.getVariables();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getVariables');
    end
  end

  function result = getBoolOption(self,tString1)
    try
      result = self.impl.getBoolOption(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getBoolOption');
    end
  end

  function show(self,varargin)
    try
      if size(varargin) > 0
        self.impl.show(varargin);
      else
        self.impl.show();
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:show');
    end
  end

  function result = getOption(self,tString1)
    try
      result = char(self.impl.getOption(tString1) );
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getOption');
    end
  end

  function setOutputHandler(self,tOutputHandler1)
    try
      self.impl.setOutputHandler(tOutputHandler1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setOutputHandler');
    end
  end

  function result = getIntOption(self,tString1)
    try
      result = self.impl.getIntOption(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getIntOption');
    end
  end

  function enableErrorRedirection(self)
    try
      self.impl.enableErrorRedirection();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:enableErrorRedirection');
    end
  end

  function result = getConstraints(self)
    try
      result = self.impl.getConstraints();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getConstraints');
    end
  end

  function result = getErrorHandler(self)
    try
      result = self.impl.getErrorHandler();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getErrorHandler');
    end
  end

  function setIntOption(self,tString1,tint2)
    try
      self.impl.setIntOption(tString1, tint2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setIntOption');
    end
  end

  function result = isRunning(self)
    try
      result = self.impl.isRunning();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:isRunning');
    end
  end

  function readDataAsync(self,tString1,tRunnable2)
    try
      self.impl.readDataAsync(tString1, tRunnable2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:readDataAsync');
    end
  end

  function solveAsync(self,tRunnable1)
    try
      self.impl.solveAsync(tRunnable1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:solveAsync');
    end
  end

  function interrupt(self)
    try
      self.impl.interrupt();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:interrupt');
    end
  end

  function evalAsync(self,tString1,tRunnable2)
    try
      self.impl.evalAsync(tString1, tRunnable2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:evalAsync');
    end
  end

  function close(self)
    try
      self.impl.close();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:close');
    end
  end

  function writeTable(self,tString1)
    try
      self.impl.writeTable(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:writeTable');
    end
  end

  function result = getData(self,varargin)
    try
      if size(varargin) > 0
        result = self.impl.getData(varargin);
      else
        result = self.impl.getData();
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getData');
    end
  end

  function result = getParameter(self,tString1)
    try
      result = self.impl.getParameter(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getParameter');
    end
  end

  function setBoolOption(self,tString1,tboolean2)
    try
      self.impl.setBoolOption(tString1, tboolean2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setBoolOption');
    end
  end

  function result = cd(self,varargin)
    try
      if size(varargin) > 0
        result = char(self.impl.cd(varargin));
      else
        result = char(self.impl.cd());
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:cd');
    end
  end

  function setOption(self,tString1,tString2)
    try
      self.impl.setOption(tString1, tString2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setOption');
    end
  end

  function result = getDblOption(self,tString1)
    try
      result = self.impl.getDblOption(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getDblOption');
    end
  end

  function result = isBusy(self)
    try
      result = self.impl.isBusy();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:isBusy');
    end
  end

  function read(self,tString1)
    try
      self.impl.read(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:read');
    end
  end

  function readData(self,tString1)
    try
      self.impl.readData(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:readData');
    end
  end

  function result = getSet(self,tString1)
    try
      result = self.impl.getSet(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getSet');
    end
  end

  function setData(self,varargin)
    try
      if size(varargin) > 0
        self.impl.setData(varargin);
      else
        self.impl.setData();
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setData');
    end
  end

  function readTable(self,tString1)
    try
      self.impl.readTable(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:readTable');
    end
  end

  function result = getOutputHandler(self)
    try
      result = self.impl.getOutputHandler();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getOutputHandler');
    end
  end

  function display(self,varargin)
    try
      if size(varargin) > 0
        self.impl.display(varargin);
      else
        self.impl.display();
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:display');
    end
  end

  function result = getObjective(self,tString1)
    try
      result = self.impl.getObjective(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getObjective');
    end
  end

  function attachShutDownHook(self)
    try
      self.impl.attachShutDownHook();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:attachShutDownHook');
    end
  end

  function result = getVariable(self,tString1)
    try
      result = self.impl.getVariable(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getVariable');
    end
  end

  function result = getValue(self,tString1)
    try
      result = self.impl.getValue(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getValue');
    end
  end

  function result = getObjectives(self)
    try
      result = self.impl.getObjectives();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getObjectives');
    end
  end

  function expand(self,varargin)
    try
      if size(varargin) > 0
        self.impl.expand(varargin);
      else
        self.impl.expand();
      end
    catch e
       HandleException(e, 'AMPLAPI:AMPL:expand');
    end
  end

  function eval(self,tString1)
    try
      self.impl.eval(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:eval');
    end
  end

  function result = getOutput(self,tString1)
    try
      result = char(self.impl.getOutput(tString1));
    catch e
      HandleException(e, 'AMPLAPI:AMPL:getOutput');
    end
  end

  function result = getConstraint(self,tString1)
    try
      result = self.impl.getConstraint(tString1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getConstraint');
    end
  end

  function setErrorHandler(self,tErrorHandler1)
    try
      self.impl.setErrorHandler(tErrorHandler1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:setErrorHandler');
    end
  end

  function solve(self)
    try
      self.impl.solve();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:solve');
    end
  end

  function result = equals(self,tObject1)
    try
      result = self.impl.equals(tObject1) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:equals');
    end
  end

  function result = getParameters(self)
    try
      result = self.impl.getParameters();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:getParameters');
    end
  end

  function reset(self)
    try
      self.impl.reset();
    catch e
       HandleException(e, 'AMPLAPI:AMPL:reset');
    end
  end

  function result = toString(self)
    try
      result = char(self.impl.toString());
    catch e
       HandleException(e, 'AMPLAPI:AMPL:toString');
    end
  end

  function readAsync(self,tString1,tRunnable2)
    try
      self.impl.readAsync(tString1, tRunnable2) ;
    catch e
       HandleException(e, 'AMPLAPI:AMPL:readAsync');
    end
  end
end
end
