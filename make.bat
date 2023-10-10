@echo off

:: Build the server
echo Building Server...
cd server
call make
cd ..

:: Build the client
echo Building Client...
cd client
call make
cd ..

:: Run the executable if "run server" was specified
if [%~1]==[run] if [%~2]==[server] (
    echo ~ Running Server...
    echo:
    call server\bin\server.exe
)

:: Run the executable if "run client" was specified
if [%~1]==[run] if [%~2]==[client] (
    echo ~ Running Client...
    echo:
    call client\bin\client.exe
)

:: Gracefully exit
echo:
echo:
echo Done.
