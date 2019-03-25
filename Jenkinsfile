pipeline {
  agent any
  stages {
    stage('Environment') {
      steps {
        sh '''
git submodule update --init;
make clean;
make env;
'''
      }
    }
    stage('Examples') {
      steps {
        sh 'make -f ${WORKSPACE}/examples/Makefile'
      }
    }
  }
}
