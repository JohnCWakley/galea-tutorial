#!/bin/bash

echo
echo "./src/galea/shaders/simple_shader.vert -> ./src/galea/shaders/simple_shader.vert.spv"
glslc ./src/galea/shaders/simple_shader.vert -o ./src/galea/shaders/simple_shader.vert.spv

echo "./src/galea/shaders/simple_shader.frag -> ./src/galea/shaders/simple_shader.frag.spv"
glslc ./src/galea/shaders/simple_shader.frag -o ./src/galea/shaders/simple_shader.frag.spv

echo
echo "done."
echo
