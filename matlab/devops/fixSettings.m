function fixSettings(mdl)
%% Old School.
set_param(mdl, 'RTWGenerateCodeOnly', 'on');

% Display Settings
set_param(mdl,'WideLines','on');
set_param(mdl,'ShowPortDataTypes','on');
set_param(mdl,'ShowStorageClass','on');
set_param(mdl,'ShowTestPointIcons','on');
set_param(mdl,'ShowLineDimensions','on');
set_param(mdl,'LibraryLinkDisplay','all');
set_param(mdl,'SampleTimeColors','on');
set_param(mdl,'SampleTimeAnnotations','on');

% Debugging
set_param(mdl,'RTWRetainRTWFile','on');

%% New School
cs = getActiveConfigSet(mdl);
cs.set_param('CustomSourceCode', '/* Insert custom c code in generated: Source file */');   % Source file
cs.set_param('CustomHeaderCode', '/* Insert custom c code in generated: Header file */');   % Header file
cs.set_param('CustomInitializer', '/* Insert custom c code in generated: Initialize function */');   % Initialize function
cs.set_param('CustomTerminator', '/* Insert custom c code in generated: Terminate function */');   % Terminate function

cs.set_param('RetainRTWFile', 'on');   % Retain .rtw file

save_system(mdl);