@echo off
set PATH=%CD%;%PATH%;
if ""%1""=="""" goto error
del temp.apk
del "%~n1_signed.apk"
java -jar %~dp0\signapk.jar %~dp0\kivvi.x509.pem %~dp0\kivvi.pk8 %1 temp.apk theGameOfAndroid
%~dp0\zipalign -v 4 temp.apk "%~n1_signed.apk"
del temp.apk
jarsigner -verify "%~n1_signed.apk"
goto end
:error
echo please use go.bat xxx.apk
:end:
