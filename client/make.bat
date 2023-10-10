@echo off

if not exist "%cd%/bin" mkdir "%cd%/bin"
g++ -std=c++17 main.cpp -o ./bin/client.exe -lws2_32
