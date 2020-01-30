#!/usr/bin/env bash

export MATLAB_PREFDIR=`pwd`/PREFDIR
/usr/local/MATLAB/R2019b/bin/matlab \
	-nosplash \
	-nosoftwareopengl \
	-r "run('build_espidf_from_templates')"  \
	-sd `pwd` \
	-logfile build_espidf_from_templates.log
