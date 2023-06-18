#version 300 es

precision mediump float;

uniform vec3 uDiffuseColor;
uniform vec3 uViewPosition;
uniform float uShinyness;
uniform sampler2D uShadowMap;
uniform vec3 uLightColor;
uniform vec3 uLightDirection;

in vec3 vNormal;
in vec3 vFragPosition;
in vec4 vShadowCoords;

out vec4 fragcolor;

float ambient = 0.7;

vec3 diffuse(vec3 normal) {
	float diff = max(dot(normal, uLightDirection), 0.0);
	return diff * uLightColor;
}

vec3 specular(vec3 normal) {
	float specularStrength = 0.5;
	vec3 viewDir = normalize(uViewPosition - vFragPosition);
	vec3 reflectDir = reflect(-uLightDirection, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShinyness);
	return specularStrength * spec * uLightColor;
}

void main() {
	vec3 normal = normalize(vNormal);
	float visibility = 1.0;
	if (texture(uShadowMap, vShadowCoords.xy).z < vShadowCoords.z) {
		visibility = 0.5;
	}
	vec3 color = (ambient + diffuse(normal) * visibility + specular(normal) * visibility) * uDiffuseColor;
	fragcolor = vec4(color, 1.0);
}