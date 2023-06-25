#version 300 es

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 aTextCoord;

out vec2 vTextCoords;

void main() {
	vTextCoords = aTextCoord;
	gl_Position = vec4(aPosition, 0.0, 1.0);
}