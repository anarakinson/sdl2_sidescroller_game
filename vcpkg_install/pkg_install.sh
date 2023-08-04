../vcpkg/vcpkg.exe install sdl2 -v 2.26.5
../vcpkg/vcpkg.exe install sdl2-image -v 2.6.3

# optionally if not installed as dependencies
../vcpkg/vcpkg.exe install zlib
../vcpkg/vcpkg.exe install libpng

# optionally add your system preferences, like: 
# ..\vcpkg\vcpkg.exe install sdl2:x64-linux
