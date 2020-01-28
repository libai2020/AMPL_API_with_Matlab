function myListener(~, output)
    % MYLISTENER can be registered to be executed by AMPL when an output is detected
    %           It accepts as an input an object of type AMPLOutput

   fprintf('(%s) AMPL: %s\n', datestr(now, 'HH:MM:SS.FFF'), output.msg);
end
