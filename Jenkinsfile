pipeline {
  agent {
    dockerfile {
      label 'docker'
      additionalBuildArgs '--build-arg USER_ID=$(id -u) --build-arg GROUP_ID=$(id -g)'
    }
  }
  options { ansiColor('xterm') }
  stages {
    stage('Init title') {
      when { changeRequest() }
      steps { script { currentBuild.displayName = "PR ${env.CHANGE_ID}: ${env.CHANGE_TITLE}" } }
    }
    stage('Build') {
      options { timeout(time: 180, unit: 'MINUTES') }
      steps {
        sh '''
          mkdir install
          cmake -S llvm -B build -G "Unix Makefiles" \
                -DLLVM_ENABLE_PROJECTS="clang"       \
                -DCMAKE_INSTALL_PREFIX=../install    \
                -DCMAKE_BUILD_TYPE=Debug             \
                -DLLVM_TARGETS_TO_BUILD="X86"
          cmake --build build -j 2 --target install
        '''
      }
    }
    stage('Test')  { steps { sh 'echo test'  } }
  }
}
