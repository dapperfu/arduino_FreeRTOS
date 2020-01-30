function startup()
fprintf('%%%% Startup set path for Arduino FreeRTOS Embedded Coder\n');
%Add path with subfolders
cwd=fileparts(mfilename('fullpath'));
addpath(cwd);
addpath(fullfile(cwd,'blocks'));
addpath(fullfile(cwd,'rtw'));
addpath(fullfile(cwd,'scripts'));
sl_refresh_customizations;
