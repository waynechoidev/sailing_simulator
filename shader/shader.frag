#version 300 es
precision mediump float;
precision mediump int;
precision mediump sampler2DArray;

in vec4 vCol;
in vec2 TexCoord;

out vec4 colour;

uniform sampler2D theTexture;

void main()
{
	colour = texture(theTexture, TexCoord);
}