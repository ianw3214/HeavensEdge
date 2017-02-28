@echo off
doskey a = atom $*
doskey ls = dir $*
doskey tx = pdflatex $*
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall"
cd "C:\Users\ianw3214\workspace\HeavensEdge"
echo on
