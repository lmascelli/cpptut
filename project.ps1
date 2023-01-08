Push-Location "build"
cmake --build .
Pop-Location
./build/test.exe
