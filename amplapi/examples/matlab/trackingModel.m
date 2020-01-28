% Simple heuristic to solve a MILP index tracking problem with cardinality
% The model and data files used are in the tracking directory.

function trackingModel(solver, modeldir)
  ampl = AMPL;
  % Initialize.
  if nargin >= 2
    modeldirectory = fullfile(modeldir, 'tracking');
  else
    basef = fileparts(which('dietModel'));
    addpath(fullfile(basef, '../../matlab'));
    modeldirectory = fullfile(basef, '..', 'models', 'tracking');
  end
  if nargin >= 1
    ampl.setOption('solver', solver);
  end

   % PARAMETERS: cutoff points,
  % for stocks which seemed very profitable at the relaxed execution
  lowcutoff = 0.04;
  highcutoff = 0.1;

  dataFile = [modeldirectory '/tracking.xls'];
  % Load from file the ampl model
  ampl.read([modeldirectory '/tracking.mod'])

  % Gets the needed entities
  asset = ampl.getSet('asset');
  astret = ampl.getParameter('astret');
  hold = ampl.getVariable('hold');
  ifin = ampl.getParameter('ifinuniverse');
  cst = ampl.getObjective('target');

  % Read the excel file for the returns
  % To keep compatibility with Linux and OSX, use xlsread in basic mode,
  % hence reading the whole file. Some manipulation is therefore required
  % to get the specific data.
  % Read the whole file
  data = xlsread(dataFile, '', '', 'basic');
  % Get the data corresponding to the returns (dimensions ntime, nassets)
  returns = data(:,7:end);
  % Generate the asset names starting from the size of the matrix above
  anames = cell(size(returns, 2), 1);
  for i=1:size(returns,2)
    anames{i} = sprintf('a%i', i);
  end
  % Assign the time index
  ampl.getSet('rtime').setValues(data(:,1));
  % Assign the index returns
  ampl.getParameter('indret').setValues(data(:,2));
  % Assigns the asset names to the corresponding ampl set
  asset.setValues(anames);
  % Assigns the asset returns to the parameter astret
  % from a MATLAB matrix
  astret.setValues(returns);

  % Relax the integerality
  ampl.setIntOption('relax_integrality', 1);
  % Solve the problem
  ampl.solve()

  % Get the variable representing the (relaxed) solution vector
  holddf = hold.getValues();
  holdvalues = holddf.getColumnAsDoubles('val');
  % For each asset, if it was held by more than the highcutoff, forces it in
  % the model, if less than lowcutoff, forces it out
  toHold = zeros(31,1);
  for i=1:length(holdvalues)
    if(holdvalues(i) < lowcutoff)
      toHold(i) = 0;
    else if(holdvalues(i) > highcutoff)
        toHold(i)= 2;
      else
        toHold(i)=1;
      end
    end
  end

  % uses those values for the parameter ifinuniverse, which controls which
  % stock is included or not in the solution
  ifin.setValues(toHold);

  % Get back to the integer problem
  ampl.setIntOption('relax_integrality', 0);
  % Solve the (integer) problem
  ampl.solve()

  % Close the AMPL object
  ampl.close();
end
