#!/usr/bin/env bash

make clean
export MATLAB_PREFDIR=`pwd`/PREFDIR
/usr/local/MATLAB/R2019b/bin/matlab \
	-nosplash \
	-nosoftwareopengl \
	-r "run('build_arduino_freertos_from_templates')"  \
	-sd `pwd` \
	-logfile build_arduino_freertos_from_templates.log
