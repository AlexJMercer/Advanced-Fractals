@REM rmdir /s /q build

@REM mkdir build

@REM cmake -S . -B build -G "Visual Studio 17 2022"

cmake --build build --config Release

@REM build\App\Release\App.exe
