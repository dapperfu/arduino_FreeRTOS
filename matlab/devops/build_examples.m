function build_examples
% Build all examples.

jenkinsfile_path = simulinkdevops.find_Jenkinsfile;



addpath(fullfile(jenkinsfile_path, 'examples'));

build_dir = fullfile(jenkinsfile_path, 'build', 'examples');
mkdir(build_dir);
cd(build_dir);

examples = dir(fullfile(jenkinsfile_path, 'examples', '*.slx'));

for example = examples'
   build_example(example); 
end