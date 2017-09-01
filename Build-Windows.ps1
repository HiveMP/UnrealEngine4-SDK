param()

$ErrorActionPreference = 'Stop'

trap
{
    Write-Error $_
    exit 1
}

Push-Location .\SDK-Generator
try
{
    yarn
    if ($LastExitCode -ne 0) { throw "yarn didn't run successfully" }
    yarn run generator -- generate UnrealEngine-4.16 dist/UnrealEngine-4.16
    if ($LastExitCode -ne 0) { throw "SDK generator didn't run successfully" }
}
catch
{
    throw;
}
finally
{
    Pop-Location
}

Copy-Item -Force -Recurse .\SDK-Generator\dist\UnrealEngine-4.16\*.h Source\Public\
Copy-Item -Force -Recurse .\SDK-Generator\dist\UnrealEngine-4.16\*.cpp Source\Public\
& "C:\Program Files\Epic Games\UE_4.16\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Rocket -Plugin="%CD%\OnlineSubsystemHive.uplugin" -Package="%CD%\..\build416" -CreateSubFolder -TargetPlatforms=Win32+Win64+Linux
if ($LastExitCode -ne 0) { throw "Unreal Engine didn't build successfully" }