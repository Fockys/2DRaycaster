The purpose of this project is to improve my own knowledge on how simple rendering for 3dlike games such as wolfenstein work.
This project is only for my educational improvement.

# Build instructions

This project uses CMake and the SDL3 development library. 

## 1) Install the required tools

You need:

- Git
- CMake 3.26 or newer
- A C compiler
  - Visual Studio 2022 Build Tools (recommended on Windows)
  - or MinGW-w64
- SDL3 development libraries

If you use Visual Studio, open a "Developer PowerShell for VS 2022" (or x64 Native Tools Command Prompt) before running the build commands.

## 2) Install SDL3

The project depends on `SDL3`. The easiest way on Windows is to install it with `vcpkg`.

```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg install sdl3:x64-windows
```

If you prefer, you can also download the official SDL3 development package from the SDL website and install it manually, but the `vcpkg` route is the simplest for CMake projects.

## 3) Clone the project

```powershell
git clone https://github.com/Fockys/2DRaycaster.git
cd 2DRaycaster
```

## 4) Configure the project with CMake

Use the vcpkg toolchain file so CMake can find SDL3.

### Option A: Visual Studio generator

```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DCMAKE_TOOLCHAIN_FILE="C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Replace `C:/path/to/vcpkg` with the path where you cloned vcpkg.

If you installed SDL3 in a different way, you may need to set the appropriate `CMAKE_PREFIX_PATH` or environment variables instead.

## 5) Build the executable

```powershell
cmake --build build --config Release
```

This will generate the executable in the build directory.

## 6) Run the executable
Run the executable through the file exlorer or command line

If SDL3 is not found at runtime, make sure the SDL3 DLL is available on your `PATH`, or copy the SDL3 runtime DLL next to the executable.


## Credits

Textures sourced from https://piiixl.itch.io/textures free for commercial and personal use