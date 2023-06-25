#version 300 es

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec3 aModelTranslation;
layout(location = 3) in vec4 aModelRotation;
layout(location = 4) in vec3 aModelScale;
layout(location = 5) in mat4 aModelMatrix;

uniform mat4 uViewProjMatrix;
uniform mat4 uLightSpaceMatrix;

out vec3 vNormal;
out vec3 vFragPosition;
out vec4 vShadowCoords;

void main() {
	vNormal = aNormal;
	vFragPosition = vec3(aModelMatrix * vec4(aPosition, 1.0));
	vShadowCoords = uLightSpaceMatrix * aModelMatrix * vec4(aPosition, 1.0);
	gl_Position = uViewProjMatrix * aModelMatrix * vec4(aPosition, 1.0);
}