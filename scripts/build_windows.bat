@ECHO OFF

conan remote add iswenzz-conan https://iswenzz.jfrog.io/artifactory/api/conan/iswenzz-conan

@REM Developer Command Prompt for Visual Studio
cd ../..
lib -machine:X86 -def:../bin/cod4x18_dedrun.def -out:libcom_plugin.lib

cd gsclib
if not exist build mkdir build
cd build
conan install .. --build --profile ../.conan/windows.conf
cmake .. -A Win32 -T ClangCL
cmake --build .
