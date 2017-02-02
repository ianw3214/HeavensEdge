@echo off
echo "+======================================================================================+"
pushd ..\build
cl ..\src\main.cpp opengl32.lib /I C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\include /I C:\Users\ianw3214\workspace\HeavensEdge\libs\glew-2.0.0\include\GL /link  C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\lib-vc2015\glfw3.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\glfw-3.2.1.bin.WIN32\lib-vc2015\glfw3dll.lib  C:\Users\ianw3214\workspace\HeavensEdge\libs\glew-2.0.0\lib\Release\Win32\glew32.lib C:\Users\ianw3214\workspace\HeavensEdge\libs\glew-2.0.0\lib\Release\Win32\glew32s.lib /SUBSYSTEM:CONSOLE
popd
echo "+======================================================================================+"
echo on
