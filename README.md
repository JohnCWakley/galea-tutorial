# galea-tutorial
This is just a repo to hold my code for learning the Vulkan API. I am following the truly amazing tutorial series by [Brenden Galea](https://www.youtube.com/channel/UC9pXmjxsQHeFH9vgCeRsHcw).

## Setup:
### Dependencies:
* [Vulkan API](https://vulkan.lunarg.com/)
* [GLFW](https://www.glfw.org/download)
* [glm](https://github.com/g-truc/glm)
* [spdlog](https://github.com/gabime/spdlog)

#### Windows 10/11:
* Add `%VULKAN_SDK%\Bin` to your PATH environment variable
* Install [tdm-gcc](https://jmeubank.github.io/tdm-gcc/download/)
* Unzip and move glfw, glm, and spdlog into `C:\SDKs` folders
  * Be sure to rename the folders like this: `glfw`, `glm`, `spdlog`
  * Or update the paths in `.vscode/c_cpp_properties.json` and `CMakeLists.txt`

#### Linux:
* Debian/Ubuntu:
    * `sudo apt install build-essential vulkan-tools libvulkan-dev vulkan-validationlayers-dev spirv-tools libglfw3-dev libglm-dev spdlog`
* Solus:
    * `$ sudo eopkg it -c system.devel`
    * `$ sudo eopkg it vulkan vulkan-headers vulkan-tools vulkan-validation-layers glm glfw-devel mesalib-devel spdlog-devel`

## Build:
(For Windows, I use Git Bash)
* `$ git clone https://github.com/JohnCWakley/vulkan`
* `$ cd vulkan`
* `$ . build.sh`
    * Note the space between `.` and `build.sh` above.
* `$ make`
* `$ ./demo`
