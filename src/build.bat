@echo off
pushd ..\build
cl ..\src\main.cpp opengl32.lib /I C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\include /link C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\lib-vc2015\glfw3.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\lib-vc2015\glfw3dll.lib /SUBSYSTEM:CONSOLE
popd
echo on
