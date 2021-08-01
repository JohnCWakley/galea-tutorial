#!/bin/bash

echo 
echo Building Shaders...
echo 

$(which glslc) ./src/shaders/simple_shader.vert -o ./src/shaders/simple_shader.vert.spv
$(which glslc) ./src/shaders/simple_shader.frag -o ./src/shaders/simple_shader.frag.spv
