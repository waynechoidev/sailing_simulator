#version 330 core

uniform mat4 model;
// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 colorVertex;

out vec3 fragmentColor;

void main(){

   gl_Position = model * vec4(pos, 1.0);

   fragmentColor = colorVertex;

}

