%% Build ; for all given templates.
%
% Generate a minimal project & generate code.
%
% Useful for:
%   Debugging templates.
%   Debugging targets.
%   Continuous integration.
script_dir = fileparts(mfilename('fullpath'));
build_dir = fullfile(script_dir, '..', 'build', 'templates');
mkdir(build_dir);
cd(build_dir);

ec_models = {
    'code_generation_system';
    'multi_rate';
    };
%  file without the stuffix.
targets = {
    'arduino_freertos';
};
% Close all models
bdclose('all');
for target_idx = 1:length(targets)
    target = targets{target_idx};
    for idx = 1:length(ec_models)
        ec_model = ec_models{idx};
        hdl = Simulink.createFromTemplate(ec_model);
        configSet = getActiveConfigSet(bdroot);
        fixSettings(hdl);
        model =  sprintf('template_%s', ec_model);
        switchTarget(configSet, sprintf('%s.tlc', target), []);
        save_system(hdl, model);
        close_system(hdl);
        open_build_save_close(model)
    end
end
