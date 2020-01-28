% This example shows how to operate with compound sets.

function compoundSet(solver, modeldir)
  % Initialize.
  ampl = AMPL;

  if nargin >= 1
    ampl.setOption('solver', solver);
  end

  % Create appropriate entities in AMPL
  ampl.eval('set CITIES; set LINKS within (CITIES cross CITIES); param cost {LINKS} >= 0; param capacity {LINKS} >= 0;');
  ampl.eval('data; set CITIES := PITT NE SE BOS EWR BWI ATL MCO;');

  % Create compound set indices

  linksFrom = {'PITT'; 'PITT'; 'NE'; 'NE';  'NE';  'SE'; 'SE'; 'SE'; 'SE'};
  linksTo = {'NE'; 'SE';'BOS';'EWR';'BWI'; 'EWR'; 'BWI';'ATL';'MCO'};
  cost = [2.5 3.5 1.7 0.7 1.3 1.3 0.8 0.2 2.1];
  capacity = [250 250 100 100 100 100 100 100 100];

  % Create dataframe.
  df = DataFrame(2, 'LINKSFrom', 'LINKSTo', 'cost', 'capacity');
  df.setColumn('LINKSFrom', linksFrom);
  df.setColumn('LINKSTo', linksTo);
  df.setColumn('cost', cost);
  df.setColumn('capacity', capacity);

  % Assign data
  ampl.setData(df, 'LINKS');

  % Check that data is correctly assigned
  ampl.display('cost')

  ampl.close();
end
