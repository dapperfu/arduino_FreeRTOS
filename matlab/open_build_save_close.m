function open_build_save_close(example)
narginchk(1, 1)
nargoutchk(0, 0)

if isstruct(example)
    [~, model, ~] = fileparts(example_struct.name);
else
    model = example;
end
open_system(model);
fixSettings(model);
slbuild(model);
save_system(model);
close_system(model);