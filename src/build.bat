@echo off
echo "+======================================================================================+"
pushd ..\build
cl /EHsc ..\src\main.cpp ..\src\engine.cc ..\src\state.cc /I ..\src\headers /I C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2-2.0.4\include /I C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2_image-2.0.1\include /I C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2_image-2.0.1\include /I C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2_mixer-2.0.1\include /link  C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2-2.0.4\lib\x86\SDL2.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2-2.0.4\lib\x86\SDL2main.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2_image-2.0.1\lib\x86\SDL2_image.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\SDL2_mixer-2.0.1\lib\x86\SDL2_mixer.lib /SUBSYSTEM:CONSOLE
popd
echo "+======================================================================================+"
echo on
