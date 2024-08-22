#version 300 es
precision mediump float;
precision mediump int;

out vec4 color;
in vec2 texCoords;

uniform sampler2D screenTexture;

void main(void)
{
	color = texture(screenTexture, texCoords);
}
