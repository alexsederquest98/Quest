# Quasr Engine
Quasar is a WIP 3D/2D game engine built in C++.

_Based on [Hazel](https://github.com/TheCherno/Hazel/tree/master) by The Cherno from his game engine series on Youtube._
***
## Getting Started
I recommend using Visual Studio 2022 as that is being used to develop Quasar. It may work on other environments but it is not officially tested or verified.
**1. Downloading the repository**
Start with cloning the repository with `git clone --recursive https://github.com/alexsederquest98/QuasarEngine.git`
The recursive cloning is necessary to add the 3rd-party library submodules. If you did not clone it recursively, you can get the submodules with `git submodule update --init` instead.

**2. Setup the solution**
I will already assume you have the VulkanSDK downloaded and the `VULKAN_SDK` environment variable set. This is currently built with Vulkan 1.3.

1. Run `GenerateProjects.bat` from the root folder to generate the Visual Studio 2022 solution.
2. From the solution, build the whole solution first. It will probably fail due to the post-build copying of the library into Sandbox for testing. Build all again and it should work.

***
## Features
- Nothing, WIP so far

## Planned Features
- 2D rendering system
- 3D PBR rendering system
- Editor program
- Integrated scripting language (Lua or C#)
- Audio system integration
- Physics system integration
- Linux support (maybe)

***
## 3rd Party Libraries
- [glfw](https://github.com/glfw/glfw) - Cross-platform windowing/input library
- [glm](https://github.com/g-truc/glm) - Math library
- [spdlog](https://github.com/gabime/spdlog) - Logging library
- [imgui](https://github.com/ocornut/imgui) - Fast UI library