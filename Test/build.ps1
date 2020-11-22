# . "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsamd64_x86.bat"
# $stdInclude = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.25.28610\include"

# $cl = "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Tools\MSVC\14.25.28610\bin\Hostx86\x86\cl.exe"
# & $cl /I$stdInclude /I../packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.3/build/native/include main.cpp ../packages/Microsoft.googletest.v140.windesktop.msvcstl.static.rt-dyn.1.8.1.3/lib/native/v140/windesktop/msvcstl/static/rt-dyn/x86/Release/gtest.lib


& "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\MSBuild.exe" Test.vcxproj /t:Rebuild /property:RuntimeLibrary=MDd