#version 300 es
precision mediump float;
precision mediump int;
precision mediump sampler2DArray;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Input vertex data, different for all executions of this shader.
in vec3 pos;
in vec3 color;

out vec3 fragmentColor;

void main(){

	gl_Position = projection * view * model * vec4(pos, 1.0);
	fragmentColor = color;
}

