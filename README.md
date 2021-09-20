# galea-tutorial
This is just a repo to hold my code for learning the Vulkan API. I am following the truly amazing tutorial series by [Brenden Galea](https://www.youtube.com/channel/UC9pXmjxsQHeFH9vgCeRsHcw).

I have also included my own [EZ Input library](https://github.com/JohnCWakley/ezi), dropped into the `src/third_party/ezi` folder.

I also use [TDM-GCC (MinGW)](https://jmeubank.github.io/tdm-gcc/)

### Dependencies:
* [Vulkan API](https://vulkan.lunarg.com/)
* [GLFW](https://www.glfw.org/download)
* [glm](https://github.com/g-truc/glm)
* [Tiny Object Loader](https://github.com/tinyobjloader/tinyobjloader) (in `src/third_party` folder)

Update `CMakeLists.txt` and `.vscode/c_cpp_properties.json` files with the location of the dependencies.

For my dev environment, I placed all dependencies (including Vulkan SDK) into a folder: `C:\Users\USER_NAME\dev\sdks`

### Build:
(For Windows, I use **Git Bash**)
* `$ git clone https://github.com/JohnCWakley/galea-tutorial`
* `$ cd galea-tutorial`
* `$ . build.sh`
    * Note the space between `.` and `build.sh` above.
* `$ make -j$(nproc)` or `make -j16` or `make`
    * `$(nproc)` returns your CPU Core count (if you don't know) to multi-thread building.
* `$ ./demo`
