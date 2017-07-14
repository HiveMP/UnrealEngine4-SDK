stage('Build') {
  node('windows') {
    dir('build') {
    }
    dir('src') {
      git scm
      bat '"C:\\Program Files\\Epic Games\\UE_4.16\\Engine\\Build\\BatchFiles\\RunUAT.bat" BuildPlugin -Rocket -Plugin="%CD%\\OnlineSubsystemHive.uplugin" -Package="%CD%\\..\\build" -CreateSubFolder -TargetPlatforms=Win32+Win64+Linux'
    }
    stash allowEmpty: true, includes: 'build/**', name: 'winbuild'
  }
}
stage('Publish') {
  node('linux') {
    unstash 'winbuild'
    withCredentials([string(credentialsId: 'github-user-token', variable: 'GITHUB_TOKEN')]) {
      sh("""
#!/bin/bash
set -e

ls

#echo "Testing upload of new version works to ensure GitHub API is responding..."
#\$GITHUB_RELEASE upload --user Protobuild --repo Protobuild.Manager --tag latest --name ProtobuildLinuxInstall-TestUpload.sh --file artifacts/Installers/Linux/install.sh 

#echo "Deleting release from GitHub before creating a new one"
#\$GITHUB_RELEASE delete --user Protobuild --repo Protobuild.Manager --tag latest || true
#git init || true
#git remote add origin git@github.com:Protobuild/Protobuild.Manager || true
#git push --delete origin latest || true

#echo "Creating a new release on GitHub"
#\$GITHUB_RELEASE release --user Protobuild --repo Protobuild.Manager --tag latest --name "Latest Release (Build \$BUILD_ID)" --description "This is an automatic release created by the build server.  Please refer to the README in the repository on how to install Protobuild Manager."

#echo "Uploading Linux installer to GitHub"
#\$GITHUB_RELEASE upload --user Protobuild --repo Protobuild.Manager --tag latest --name ProtobuildLinuxInstall.sh --file artifacts/Installers/Linux/install.sh 

#echo "Uploading MacOS installer to GitHub"
#\$GITHUB_RELEASE upload --user Protobuild --repo Protobuild.Manager --tag latest --name ProtobuildMacOSInstall.sh --file artifacts/Installers/MacOS/install.sh 

#echo "Uploading Windows installer to GitHub"
#\$GITHUB_RELEASE upload --user Protobuild --repo Protobuild.Manager --tag latest --name ProtobuildWindowsInstall.exe --file artifacts/Installers/Windows/ProtobuildWebInstall.exe

#echo "Done!"
""")
    }
  }
}