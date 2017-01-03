#version 150

in vec4 vertexPosition;
in vec2 vertexUV;
in vec3 vertexNormal;

out vec2 fragUV;
out vec3 fN;
out vec3 fE;
out vec3 fL;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform vec4 LightPos;

void main() {
	gl_Position = proj * view * model * vertexPosition;

	vec3 pos = (view * model * vertexPosition).xyz;

	fN = (view * model * vec4(vertexNormal, 0.0)).xyz;
	fE = -pos;
	fL = (view * LightPos).xyz - pos;

	fragUV = vec2(1.0 - vertexUV.x, vertexUV.y);
}
