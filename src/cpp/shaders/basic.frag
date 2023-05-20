#version 300 es

precision mediump float;

uniform vec3 uDiffuseColor;
uniform vec3 uViewPosition;
uniform float uShinyness;

in vec3 vNormal;
in vec3 vFragPosition;

out vec4 fragcolor;

vec3 LIGHT_COLOR = vec3(1.0, 1.0, 1.0);
vec3 LIGHT_DIRECTION = normalize(vec3(0, 1, 0));

float ambient = 0.7;

vec3 diffuse(vec3 normal) {
	float diff = max(dot(normal, LIGHT_DIRECTION), 0.0);
	return diff * LIGHT_COLOR;
}

vec3 specular(vec3 normal) {
	float specularStrength = 0.5;
	vec3 viewDir = normalize(uViewPosition - vFragPosition);
	vec3 reflectDir = reflect(-LIGHT_DIRECTION, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), uShinyness);
	return specularStrength * spec * LIGHT_COLOR;
}

void main() {
	vec3 normal = normalize(vNormal);
	vec3 color = (ambient + diffuse(normal) + specular(normal)) * uDiffuseColor;
	fragcolor = vec4(color, 1.0);
}