properties([pipelineTriggers([upstream(
  threshold: hudson.model.Result.SUCCESS,         
  upstreamProjects: "HiveMP/hivemp")])])
stage('Build') {
  node('windows') {
    dir('build416') {
    }
    dir('src') {
      checkout scm
      bat '"C:\\Program Files\\Epic Games\\UE_4.16\\Engine\\Build\\BatchFiles\\RunUAT.bat" BuildPlugin -Rocket -Plugin="%CD%\\OnlineSubsystemHive.uplugin" -Package="%CD%\\..\\build416" -CreateSubFolder -TargetPlatforms=Win32+Win64+Linux'
      bat 'xcopy /C /F /R generate.bat ..\\build416\\generate.bat'
    }
    stash allowEmpty: true, includes: 'build416/**', name: 'winbuild416'
  }
}
stage('Publish') {
  node('linux') {
    unstash 'winbuild416'
    withCredentials([string(credentialsId: 'HiveMP-Deploy', variable: 'GITHUB_TOKEN')]) {
      sh("""
#!/bin/bash
set -e

echo "Creating 4.16 version SDK..."
rm -Rf OnlineSubsystemHive || true
mv build416 OnlineSubsystemHive
zip -r UE4.16-Plugin.zip OnlineSubsystemHive/
rm -Rf OnlineSubsystemHive || true

echo "test" > test.txt

echo "Testing upload of new version works to ensure GitHub API is responding..."
\$GITHUB_RELEASE upload --user HiveMP --repo UnrealEngine4-SDK --tag latest --name TestUpload --file test.txt

echo "Deleting release from GitHub before creating a new one"
\$GITHUB_RELEASE delete --user HiveMP --repo UnrealEngine4-SDK --tag latest || true
git init || true
git remote add origin git@github.com:HiveMP/UnrealEngine4-SDK || true
git push --delete origin latest || true

echo "Creating a new release on GitHub"
\$GITHUB_RELEASE release --user HiveMP --repo UnrealEngine4-SDK --tag latest --name "Latest Release (Build \$BUILD_ID)" --description "This is an automatic release created by the build server.  Please refer to the README in the repository on how to use the HiveMP SDK in your game."

echo "Uploading 4.16 SDK to GitHub"
\$GITHUB_RELEASE upload --user HiveMP --repo UnrealEngine4-SDK --tag latest --name UE4.16-Plugin.zip --file UE4.16-Plugin.zip

echo "Done!"
""")
    }
  }
}