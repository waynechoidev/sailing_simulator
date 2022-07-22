#version 330 core

uniform mat4 model;
uniform mat4 projection;

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 pos;
//layout(location = 1) in vec3 colorVertex;


void main(){

	gl_Position = projection * model * vec4(pos, 1.0);

}

