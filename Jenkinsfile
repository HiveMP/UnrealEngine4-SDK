stage('Build') {
    node('windows') {
        dir('build') {
        }
        dir('src') {
            git scm
            bat '"C:\\Program Files\\Epic Games\\UE_4.16\\Engine\\Build\\BatchFiles\\RunUAT.bat" BuildPlugin -Rocket -Plugin="%CD%\\OnlineSubsystemHive.uplugin" -Package="%CD%\\..\\build" -CreateSubFolder -TargetPlatforms=Win32+Win64+Linux'
        }
        archiveArtifacts 'build/**'
    }
}