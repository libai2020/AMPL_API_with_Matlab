function exampleInterpreting(solver, modeldir)
  % Initialize.
  basef = fileparts(which('exampleInterpreting'));
  addpath(fullfile(basef, '../../matlab'));
  ampl = AMPL;

  if nargin >= 1
    ampl.setOption('solver', solver);
  end

  % Create various entities
  ampl.eval('set S := 1..5;');
  ampl.eval('param c{S} default 0;');
  ampl.eval('var x >= 5;');
  ampl.eval('var y{s in S} >= c[s];');
  ampl.eval('minimize o: x + sum{i in S} y[i];');

  % If 1 then Ampl is running correctly
  if (ampl.isRunning)
      disp('Ampl is correctly running before solve')
  else
     error('Ampl is not running, have you checked the binary folder?')
  end
  % Solve
  ampl.solve

  % If 1 then Ampl is running correctly
  if (ampl.isRunning)
      disp('Ampl is correctly running after solve')
  else
      error('Ampl is not running after solve')
  end

  % Get the objects corrresponding to the ampl entities
  x = ampl.getVariable('x');
  y = ampl.getVariable('y');
  o = ampl.getObjective('o');
  c = ampl.getParameter('c');
  S = ampl.getSet('S');

  % Display the value of
  data = [1 3 6 7 9];
  c.setValues(data);
  ampl.solve

  % Close the AMPL object
  ampl.close();
end
