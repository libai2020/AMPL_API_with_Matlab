function [haserror] = fileExists(filename)
fileId = fopen(filename);
haserror = (fileId == -1);

if(fileId == -1)
else
    fclose(fileId);
end
end
