@echo off

if not exist "%cd%/bin" mkdir "%cd%/bin"
g++ -std=c++17 main.cpp -o ./bin/server.exe -lws2_32
