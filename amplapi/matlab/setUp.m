% Set the paths to AMPLAPI JAR and matlab wrappers
function setUp()
  javaclasspath('-dynamic')
  base = fileparts(which('setUp'));

  % file names
  javaapiname = 'ampl-2.0.1.0.jar';
  matlabbridgename = 'matlab-lib.jar'
  if ispc
    binlibraryname = fullfile('bin', 'ampl-2.0.1.0.dll');
    binbase = fullfile(base, '..', 'bin');
  elseif ismac
    binlibraryname = fullfile('lib', 'libampl.2.0.1.0.dylib');
    binbase = fullfile(base, '..', 'lib');
  else
    binlibraryname = fullfile('lib', 'libampl.so.2.0.1.0');
    binbase = fullfile(base, '..', 'lib');
  end

  % Build full paths
  javaapi = fullfile(base, '..', 'lib', javaapiname);
  matlabbridge = fullfile(base, '..', 'matlab', matlabbridgename);
  binlibrary = fullfile(base, '..', binlibraryname);

  % Check for file existence
  if(fileExists(javaapi)~=0)
    error(['Cannot find Java AMPL API in ', javaapi])
  end
  if(fileExists(matlabbridge)~=0)
    error(['Cannot find Matlab API helper in ', matlabbridge])
  end
  if(fileExists(binlibrary)~=0)
    error(['Cannot find C++ AMPL API in ', binlibrary])
  end

  if exist('com.ampl.AMPL') ~= 8
    javaaddpath(matlabbridge);
    com.ampl.MatlabUtil.addLibraryPath(binbase)
    java.lang.System.load(binlibrary);
    javaaddpath(javaapi);
    addpath(base);
  end

  disp(['Using native binary at ', binlibrary])
  disp(['Using api at ', javaapi])
  disp(['Using wrapper at ', base])
end
