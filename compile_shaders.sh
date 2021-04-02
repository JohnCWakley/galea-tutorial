#!/bin/bash

echo
echo "./src/shaders/simple_shader.vert -> ./src/shaders/simple_shader.vert.spv"
glslc ./src/shaders/simple_shader.vert -o ./src/shaders/simple_shader.vert.spv
# $HOME/dev/vulkansdk-linux-x86_64-1.2.170.0/1.2.170.0/x86_64/bin/glslc ./src/shaders/simple_shader.vert -o ./src/shaders/simple_shader.vert.spv

echo "./src/shaders/simple_shader.frag -> ./src/shaders/simple_shader.frag.spv"
glslc ./src/shaders/simple_shader.frag -o ./src/shaders/simple_shader.frag.spv
# $HOME/dev/vulkansdk-linux-x86_64-1.2.170.0/1.2.170.0/x86_64/bin/glslc ./src/shaders/simple_shader.frag -o ./src/shaders/simple_shader.frag.spv

echo
echo "done."
echo
