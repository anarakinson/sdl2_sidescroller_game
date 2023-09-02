..\vcpkg\vcpkg.exe install sdl2 -v 2.26.5
..\vcpkg\vcpkg.exe install sdl2-image -v 2.6.3
..\vcpkg\vcpkg.exe install sdl2-mixer -v 2.6.3

@REM optionally if not installed as dependencies
..\vcpkg\vcpkg.exe install zlib
..\vcpkg\vcpkg.exe install libpng

@REM optionally add your system preferences, like: 
@REM ..\vcpkg\vcpkg.exe install sdl2:x64-windows
