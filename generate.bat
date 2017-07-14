@echo off
cd %~dp0

SET TT=""
SET HASTT=false
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\TextTransform.exe" (
    SET TT="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\TextTransform.exe"
    SET HASTT=true
)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE\TextTransform.exe" (
    SET TT="C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\Common7\IDE\TextTransform.exe"
    SET HASTT=true
)
if exist "D:\Visual Studio\Common7\IDE\TextTransform.exe" (
    SET TT="D:\Visual Studio\Common7\IDE\TextTransform.exe"
    SET HASTT=true
)

IF "%HASTT%" == "false" GOTO End

%TT% -r Newtonsoft.Json\Newtonsoft.Json.dll Source\Public\HiveBlueprintLibrary.tt
%TT% -r Newtonsoft.Json\Newtonsoft.Json.dll Source\Public\HiveBlueprintLibraryImpl.tt

:End