% Efficient frontier

function efficientFrontier(solver, modeldir)
  % PARAMETERS: cutoff points,
  % for stocks which seemed very profitable at the relaxed execution
  lowcutoff = 0.04;
  highcutoff = 0.1;
  steps = 30;


  % Initialisation
  ampl = AMPL;
  if nargin >= 2
    modeldirectory = fullfile(modeldir, 'qpmv');
  else
    basef = fileparts(which('efficientFrontier'));
    addpath(fullfile(basef, '../../matlab'));
    modeldirectory = fullfile(basef, '..', 'models', 'qpmv');
  end
  if nargin >= 1
    ampl.setOption('solver', solver);
  end

  modelFile = fullfile(modeldirectory, 'qpmv.mod');
  scriptFile = fullfile(modeldirectory, 'qpmvbit.run');

  if nargin >= 1
    ampl.setOption('solver', solver);
  end

  % Load from file the ampl model
  ampl.read(modelFile)
  % Load the data tables declaration
  ampl.read(scriptFile);
  % Set the data file location (used in the script)
  ampl.getParameter('data_dir').set(modeldirectory);

  % Load the data tables
  ampl.readTable('assetstable');
  ampl.readTable('astrets');


  % Gets the needed entities
  portfolioReturn = ampl.getVariable('portret');
  averageReturn = ampl.getParameter('averret');
  targetReturn = ampl.getParameter('targetret');
  hold = ampl.getVariable('weights');
  deviation = ampl.getObjective('cst');

  ampl.eval('let stockopall:={};let stockrun:=stockall;');
  % Relax the integerality
  ampl.setBoolOption('relax_integrality', true);

  % Solve the problem
  ampl.solve()
  % Calibrate the efficient frontier range
  minret = portfolioReturn.getValues().getColumnAsDoubles('portret.val');
  maxret = max(averageReturn.getValues().getColumnAsDoubles('averret'));
  stepsize = (maxret-minret)/steps;
  % Create the vectors to store the returns and the deviations
  returns = zeros(steps, 1);
  deviations = zeros(steps, 1);

  % applies a small heuristic (similar to trackingheuristic) to speed up the
  % solution of the efficient frontier problems at each step
  for i=1:steps
    currentReturn =  maxret - (i-1)*stepsize;
    fprintf('Solving for return = %f\n',currentReturn )
    targetReturn.setValues(currentReturn);
    ampl.eval('let stockopall:={};let stockrun:=stockall;');
    ampl.eval('options relax_integrality 1;');
    ampl.solve();
    fprintf('QP result = %f ', deviation.value())
    ampl.eval('let stockrun:={i in stockrun:weights[i]>0};');
    ampl.eval('let stockopall:={i in stockrun:weights[i]>0.5};');
    ampl.setBoolOption('relax_integrality', false);
    ampl.solve();
    fprintf(' QMIP result = %f\n ', deviation.value());
    returns(i) = maxret - (i-1)*stepsize;
    deviations(i) = deviation.value();
  end

  plot(returns, deviations)

  % Close the AMPL object
  ampl.close();
end
