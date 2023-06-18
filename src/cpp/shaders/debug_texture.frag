#version 300 es

precision mediump float;

uniform sampler2D uTexture;

in vec2 vTextCoords;

out vec4 fragcolor;

void main() {
	float depthValue = texture(uTexture, vTextCoords).r;
	fragcolor = vec4(vec3(depthValue), 1.0);
}