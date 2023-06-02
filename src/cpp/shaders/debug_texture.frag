#version 300 es

precision mediump float;

uniform sampler2D uTexture;

in vec2 vTextCoords;

out vec4 fragcolor;

void main() {
	fragcolor = texture(uTexture, vTextCoords);
}