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
          pwd()
          sh 'make -f ${WORKSPACE}/examples/Makefile'
        }

      }
    }
    stage('Example2') {
      steps {
        timestamps() {
          dir(path: '${WORKSPACE}/examples') {
            recordIssues(aggregatingResults: true, enabledForFailure: true)
            sh '''# Clean & Build
make clean;
make -j6'''
          }

        }

      }
    }
  }
}