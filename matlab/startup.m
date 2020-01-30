function startup()
fprintf('%%%% Startup set path for Arduino FreeRTOS Embedded Coder\n');
fprintf('%%%% Simulink DevOps\n');
%Add path with subfolders
cwd=fileparts(mfilename('fullpath'));
addpath(cwd);
addpath(fullfile(cwd,'blocks'));
addpath(fullfile(cwd,'rtw'));
addpath(fullfile(cwd,'scripts'));
addpath(fullfile(cwd,'scripts', 'init'));
addpath(fullfile(cwd,'devops'));
sl_refresh_customizations;