@ECHO OFF

@REM Developer Command Prompt for Visual Studio
cd ../..
lib -machine:X86 -def:bin/cod4x18_dedrun.def -out:plugins/libcom_plugin.lib
