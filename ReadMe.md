## How to Build and Run Arrow2D

### Prerequisites
* [CMake](https://cmake.org/download/)
* [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/)
* [vcpkg](https://github.com/microsoft/vcpkg)

### Steps
1. **Install SDL3 using vcpkg**
   Open PowerShell and run:
   ```powershell
   & "C:\Program Files\vcpkg\vcpkg.exe" install sdl3:x64-windows
   & "C:\Program Files\vcpkg\vcpkg.exe" install sdl3-ttf:x64-windows
   & "C:\Program Files\vcpkg\vcpkg.exe" integrate install
   ```


2. **Configure, build, and run the project**
   From your project root directory, run:
   ```powershell
   mkdir build
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="C:/Program Files/vcpkg/scripts/buildsystems/vcpkg.cmake"
   cmake --build build
   .\build\Debug\Arrow2D.exe
   ```

---
If you encounter issues, make sure your vcpkg path matches your installation and all prerequisites are installed.
