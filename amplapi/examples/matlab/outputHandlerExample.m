% Redirecting AMPL output
% Note that due to MATLAB architecture, output redirection only works
% if access to the AMPL API jar file is set up statically (e.g. via the
% command edit('classpath.txt') ). To execute this example the classpath
% must be edited BEFORE calling setupOnce, and MATLAB must be restarted.

% The pause commands are needed to give MATLAB time to update the handlers
% while AMPL executes in the background

function outputHandlerExample(solver, modeldir)
  % create an AMPL interpreter
  ampl = AMPL;
  ampl.eval('print "Normal ampl!";');

  % initialize the redirection subsystem, making the AMPL output pass
  % through MATLAB.
  ampl.initializeEvents;

  % try printing something
  ampl.eval('print "No listener registered";');
  pause(0.1)
  % add a listener implemented with a function (see myListener.m)
  lh = addlistener(ampl, 'Output', @myListener);
  pause(0.1)
  % test out that listener
  ampl.eval('for {i in 1..10} { printf "this is the %i execution", i;}');

  pause(1)
  % remove the listener previously defined
  delete(lh)
  pause(0.1)
  % try printing something
  ampl.eval('print "No listener registered!";');
end
