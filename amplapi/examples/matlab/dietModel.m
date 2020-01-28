% Show data communication to and from MATLAB

function dietModel(solver, modeldir)
  ampl = AMPL;
  % Initialize.
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

  % Load from file the ampl model
  ampl.read([modeldirectory  '/diet.mod']);

  % ASSIGN DATA METHOD 1 (using dataframe)
  % Input values for nutritional values
  NUTR = {'A';  'B1';'B2';'C';'CAL';'NA'};
  n_min_values = [700; 700; 700; 700; 16000; 0];
  n_max_values = [20000; 20000; 20000; 20000; 24000; 50000];
  % Populate a dataframe with the values
  df = DataFrame(1, 'NUTR', 'n_min', 'n_max');
  df.setColumn('NUTR', NUTR);
  df.setColumn('n_min', n_min_values);
  df.setColumn('n_max', n_max_values);
  df.toTable()
  % Assign them to the corresponding AMPL entities
  % the matching is done automatically by name
  % The true in the function specifies to assign the values of the sets too
  ampl.setData(df, 'NUTR');

  % ASSIGN DATA METHOD 2 (directly to the entities)
  % Note that assigning the parameters in the way below depends on the
  % internal ordering that AMPL assigns to the set members
  FOOD = {'BEEF' ; 'CHK'; 'FISH';'HAM';'MCH';'MTL';'SPG';'TUR'};
  food = ampl.getSet('FOOD');
  food.setValues(FOOD);
  % With reference
  f_min = ampl.getParameter('f_min');
  f_min.setValues(ones(1,8)*2);
  % Single line
  ampl.getParameter('f_max').setValues(ones(1,8)*10);
  % From a vector
  ampl.getParameter('cost').setValues([3.19, 2.59, 2.29, 2.89, 1.89, 1.99, 1.99, 2.49])

  % ASSIGN DATA METHOD 3: MATLAB matrix via DataFrame
  due = [60   10   15   20   295    938 ; 8   20   20    0   770   2180; 8   15   10   10   440    945;  40   25   10   40   430    278;  15   15   15   35   315   1182;  70   15   15   30   400    896;   25   25   15   50   370   1329; 60   15   10   20   450   1397];
  % Create empty dataframe with headings which have the same name as the corrresponding
  % AMPL entities
  df = DataFrame(2, 'NUTR', 'FOOD', 'amt');
  % Set the values in the DataFrame
  df.setMatrix(transpose(due), NUTR, FOOD);
  df.toTable()
  % Set the values to the parameter
  ampl.setData(df);
  % Check that assignment worked correctly
  ampl.display('amt')

  % Solve
  ampl.solve

  % Get solution vector and dual values to a DataFrame object
  Buy = ampl.getVariable('Buy');
  df = Buy.getValues('val', 'dual');
  % Display dataframe
  df
  % Convert the DataFrame to a MATLAB table
  df.toTable()
  % Get values to MATLAB vector
  values = df.getColumnAsDoubles('Buy.val');

  ampl.close()
end
