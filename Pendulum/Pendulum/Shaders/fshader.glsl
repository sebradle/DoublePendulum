#version 150

in vec2 fragUV;
in vec3 fN;
in vec3 fL;
in vec3 fE;

out vec4 color;

uniform sampler2D mySampler;
uniform vec4 Ambient;
uniform vec4 Diffuse; 
uniform vec4 Specular;
uniform vec4 ka;
uniform vec4 kd;
uniform vec4 ks;
uniform float Shininess;
uniform bool light_out;
uniform bool texture_on;
uniform vec4 LightPos;
uniform mat4 view;

vec4 kA, kD, kS;

void main(){
	vec3 N = normalize(fN);
	if (light_out) N = -N;

	vec3 E = normalize(fE);
	vec3 L = normalize(fL);

	vec3 H = normalize( L + E );

	vec4 textureColor = vec4(1.0, 1.0, 1.0, 1.0);
	if(texture_on)
	{
		textureColor = texture(mySampler, fragUV);
		kA = vec4(1.0,1.0,1.0,1.0);
		kD = vec4(1.0,1.0,1.0,1.0);
		kS = vec4(0.9,0.9,0.9,1.0);
	}
	else
	{
		kA = ka;
		kD = kd;
		kS = ks;
	}

	vec4 ambient = Ambient * kA * textureColor;
	vec4 diffuse; 
	if(light_out) diffuse = Diffuse * kD * textureColor * max( dot(L,N), 0.0);
	else diffuse = Diffuse * kD * textureColor * max( dot(L,N), 0.0) / (0.1 * pow(length(fL),2.0));

	vec4 specular = Specular * kS * textureColor * pow( max(dot(reflect(-L,N), E), 0.0), Shininess);
	if( dot(L,N) < 0.0 ) specular = vec4(0.0, 0.0, 0.0, 1.0);

	color = ambient + diffuse + specular;
	color.a = ka.a;
}