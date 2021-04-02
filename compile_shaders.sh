#!/bin/bash

# /home/havoc/android_sdk/ndk/21.4.7075529/shader-tools/linux-x86_64/glslc ./src/shaders/simple_shader.vert -o ./src/shaders/simple_shader.vert.spv
# /home/havoc/android_sdk/ndk/21.4.7075529/shader-tools/linux-x86_64/glslc ./src/shaders/simple_shader.frag -o ./src/shaders/simple_shader.frag.spv

$HOME/dev/vulkansdk-linux-x86_64-1.2.170.0/1.2.170.0/x86_64/bin/glslc ./src/shaders/simple_shader.vert -o ./src/shaders/simple_shader.vert.spv
$HOME/dev/vulkansdk-linux-x86_64-1.2.170.0/1.2.170.0/x86_64/bin/glslc ./src/shaders/simple_shader.frag -o ./src/shaders/simple_shader.frag.spv