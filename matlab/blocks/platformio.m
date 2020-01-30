function platformio(block)
%MSFUNTMPL_BASIC A Template for a Level-2 MATLAB S-Function
%   The MATLAB S-function is written as a MATLAB function with the
%   same name as the S-function. Replace 'msfuntmpl_basic' with the 
%   name of your S-function.
%
%   It should be noted that the MATLAB S-function is very similar
%   to Level-2 C-Mex S-functions. You should be able to get more
%   information for each of the block methods by referring to the
%   documentation for C-Mex S-functions.
%
%   Copyright 2003-2010 The MathWorks, Inc.

%%
%% The setup method is used to set up the basic attributes of the
%% S-function such as ports, parameters, etc. Do not add any other
%% calls to the main body of the function.
%%
setup(block);

%endfunction

%% Function: setup ===================================================
%% Abstract:
%%   Set up the basic characteristics of the S-function block such as:
%%   - Input ports
%%   - Output ports
%%   - Dialog parameters
%%   - Options
%%
%%   Required         : Yes
%%   C-Mex counterpart: mdlInitializeSizes
%%
function setup(block)
% Register number of ports
block.NumInputPorts  = 0;
block.NumOutputPorts = 0;

% Setup port properties to be inherited or dynamic
block.SetPreCompInpPortInfoToDynamic;
block.SetPreCompOutPortInfoToDynamic;

for i=1:block.NumInputPorts
    block.InputPort(i).Dimensions  = 1;
    block.InputPort(i).DatatypeID  = 8; % boolean
    block.InputPort(i).Complexity  = 'Real';
    block.InputPort(i).SamplingMode  = 0;
end

for i=1:block.NumOutputPorts
    block.OutputPort(i).Dimensions  = 1;
    block.OutputPort(i).DatatypeID  = 8; % boolean
    block.OutputPort(i).Complexity  = 'Real';
    block.OutputPort(i).SamplingMode  = 0;
end

% Register parameters
block.NumDialogPrms     = 0;
% Register sample times
%  [0 offset]            : Continuous sample time
%  [positive_num offset] : Discrete sample time
%
%  [-1, 0]               : Inherited sample time
%  [-2, 0]               : Variable sample time
% if length(block.DialogPrm(block.NumDialogPrms).Data)==1
%     block.SampleTimes = [block.DialogPrm(block.NumDialogPrms).Data 0];
% else
%     block.SampleTimes = block.DialogPrm(block.NumDialogPrms).Data;
% end
% Specify the block simStateCompliance. The allowed values are:
%    'UnknownSimState', < The default setting; warn and assume DefaultSimState
%    'DefaultSimState', < Same sim state as a built-in block
%    'HasNoSimState',   < No sim state
%    'CustomSimState',  < Has GetSimState and SetSimState methods
%    'DisallowSimState' < Error out when saving or restoring the model sim state
block.SimStateCompliance = 'DefaultSimState';

%% -----------------------------------------------------------------
%% The MATLAB S-function uses an internal registry for all
%% block methods. You should register all relevant methods
%% (optional and required) as illustrated below. You may choose
%% any suitable name for the methods and implement these methods
%% as local functions within the same file. See comments
%% provided for each function for more information.
%% -----------------------------------------------------------------

% Used functions.
block.RegBlockMethod('WriteRTW', @WriteRTW);
block.RegBlockMethod('PostPropagationSetup', @DoPostPropSetup);

% Null functions.
block.RegBlockMethod('Outputs', @nullFCN);   % Required
block.RegBlockMethod('Start', @nullFCN);   % Required
block.RegBlockMethod('Update', @nullFCN); % Required
block.RegBlockMethod('Terminate', @nullFCN); % Required
block.RegBlockMethod('InitializeConditions', @nullFCN); % Required
block.RegBlockMethod('InitializeConditions', @nullFCN); % Required

%% Block runs on TLC in accelerator mode.
block.SetAccelRunOnTLC(true);

function nullFCN(~)
%end function

function DoPostPropSetup(block)
%% Register all tunable parameters as runtime parameters.
block.AutoRegRuntimePrms;
%end function

function WriteRTW(block)
for field = get_param(block.BlockHandle, 'MaskNames')'
    block.WriteRTWParam('string', field{1}, get_param(block.BlockHandle, field{1}));
end
%end function