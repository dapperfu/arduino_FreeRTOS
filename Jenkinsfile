pipeline {
  agent any
  stages {
    stage('Environment') {
      steps {
        sh '''make clean;
make env;'''
      }
    }
    stage('Examples') {
      steps {
        sh 'make -f ${WORKSPACE}/examples/Makefile'
      }
    }
  }
}