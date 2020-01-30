cd('blocks');
disp('Opening System');
load_system('test_esp_idf_gpio');
disp('Building System')
slbuild('test_esp_idf_gpio');
exit(0);
