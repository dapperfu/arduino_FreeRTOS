pipeline {
  agent any
  stages {
    stage('Environment') {
      steps {
        sh '''# Shell Script
git submodule update --init;
make env;
'''
      }
    }
    stage('Examples') {
      steps {
        timestamps() {
          sh 'make -f ${WORKSPACE}/examples/Makefile'
          scanForIssues()
        }

      }
    }
  }
}