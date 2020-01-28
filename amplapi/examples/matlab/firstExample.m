function firstExample(solver, modeldir)
  % Create an AMPL instance
  ampl = AMPL;

  if nargin >= 2
    modeldirectory = fullfile(modeldir, 'diet');
  else
    basef = fileparts(which('dietModel'));
    addpath(fullfile(basef, '../../matlab'));
    modeldirectory = fullfile(basef, '..', 'models', 'diet');
  end
  if nargin >= 1
    ampl.setOption('solver', solver);
  end

  % Display version
  ampl.eval('option version;');


  % Load from file the ampl model
  ampl.read([modeldirectory  '/diet.mod']);
  ampl.readData([modeldirectory  '/diet.dat']);

  % Solve
  ampl.solve

  % Get objective map by AMPL name
  totalcost = ampl.getObjective('total_cost');
  % Print it
  fprintf('Objective is: %f\n' ,totalcost.value());

  % Reassign data - specific instances
  cost = ampl.getParameter('cost');
  cost.setValues({'BEEF';'HAM'}, [5.01; 4.55]);
  disp('Increased costs of beef and ham.');

  % Resolve and display objective
  ampl.solve();
  fprintf('New objective value: %f\n', totalcost.value());

  % Reassign data - all instances
  cost.setValues([3, 5, 5, 6, 1, 2, 5.01, 4.55]);

  disp('Updated all costs');
  % Resolve and display objective
  ampl.solve();
  fprintf('New objective value: %f\n', totalcost.value());

  % Get the values of the variable Buy in a dataframe object
  buy = ampl.getVariable('Buy');
  df = buy.getValues;
  % Print them
  df

  % Close the AMPL object
  ampl.close();
end
