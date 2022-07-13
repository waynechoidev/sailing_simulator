#version 330 core

uniform float Position;
// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;

void main(){

    gl_Position.x = vertexPosition_modelspace.x;
    gl_Position.y = vertexPosition_modelspace.y + Position;;
    gl_Position.z = vertexPosition_modelspace.z;
    gl_Position.w = 1.0;

}

