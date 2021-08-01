#!/bin/bash

echo 
echo Building Shaders...
echo 

$(which glslc) ./src/galea/shaders/simple_shader.vert -o ./src/galea/shaders/simple_shader.vert.spv
$(which glslc) ./src/galea/shaders/simple_shader.frag -o ./src/galea/shaders/simple_shader.frag.spv
