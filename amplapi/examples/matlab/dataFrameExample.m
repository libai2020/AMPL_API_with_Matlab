% Example to illustrate the usage of the dataframe object

function dataFrameExample(solver, modeldir)
  % Initialize.
  basef = fileparts(which('dataFrameExample'));
  addpath(fullfile(basef, '../../matlab'));

  % Single dimension
  % Create a vector of four random numbers
  A = randn(4,1);
  % Create a vector of indices
  A1 = {'a1' , 'a2', 'a3' , 'a4'};
  % Create a dataframe with 1 index
  df = DataFrame(1, 'A1', 'Values');
  % Assign the vector
  df.setMatrix(A, A1)
  % Display the dataframe
  df

  % Create a 4x3 matrix
  A = [1 2 3; 4 5 6; 7 8 9; 10 11 12];
  % First index (cardinality = number of rows
  A1 = {'a1' ; 'a2'; 'a3' ; 'a4'};
  % Second index (cardinality = number of columns)
  A2 = {1; 2; 3};
  % Create a dataframe with two idexing columns and
  % a data column called TheParameter
  df = DataFrame(2, 'A1', 'A2', 'TheParameter');
  % Assign the matrix to the dataframe
  df.setMatrix(A, A1, A2)

  % Create an AMPL instance
  ampl = AMPL;
  % Create two sets and a parameter. The name of the parameter
  % has to be the same as the column in our dataframe.
  % Sets name can differ, since we are not assigning them using
  % AMPL.setData
  ampl.eval('set S1; set S2; param TheParameter{S1, S2};');
  % Set the data for sets S1 and S2
  ampl.getSet('S1').setValues(A1);
  ampl.getSet('S2').setValues(A2);
  ampl.setData(df);
  ampl.display('TheParameter')

  % Create a new dataframe
  df = DataFrame(2, 'A1', 'A2', 'TheParameter');
  % Create a 2-d cell array
  cellArray = {'r1c1', 'r1c2', 'r1c3'; 'r2c1', 'r2c2', 'r2c3'; 'r3c1', 'r3c2','r3c3'; 'r4c1', 'r4c2', 'r4c3'}
  % assign it to the dataframe

  df.setMatrix(cellArray, A1, A2)
  % display the dataframe
  df

  % Create a 3-d matrix
  B = randn(4,3,2);
  % Create indices with various types
  B1 = {'a1' , 'a2', 4 , 'a4'};
  B2 = {'1', 'b2', 'b3'};
  B3 = {'c1', 'c2'};
  % Create dataframe
  df = DataFrame(3, 'B1', 'B2', 'B3', 'Value')
  % Assign the matrix
  df.setMatrix(B, B1, B2, B3)
  % Display the contents
  df

  % Create a 4-d matrix
  B = randn(2,2,2,2);
  % Create 4 sets of indices of cardinality 2 and of various types
  % (both strings and numbers)
  B1 = {'a1', 4};
  B2 = {'1', '4'};
  B3 = {'c1' ,'2'};
  B4 = {4, '4'};
  % Create a dataframe with 4 index columns
  df = DataFrame(4, 'B1', 'B2', 'B3', 'B4', 'Value')
  % Assign the valuees to the dataframe
  df.setMatrix(B, B1, B2, B3, B4)
  % Display the contents
  df

  % Convert DataFrame to MATLAB Matrix
  ampl.eval('param mat{i in 1..10, j in 1..10} = i+j;');
  df = ampl.getParameter('mat').getValues()
  M = zeros(10, 10);
  for i = 1: df.getNumRows()
     row = df.getRowByIndex(i);
     M(row{1}, row{2}) = row{3};
  end
  M

  % Convert DataFrame to MATLAB table
  t = df.toTable()
  t.index0 = cell2mat(t.index0);
  t.index1 = cell2mat(t.index1);
  t.mat = cell2mat(t.mat);
  t
  mean(t.mat)

  ampl.close();
end  
