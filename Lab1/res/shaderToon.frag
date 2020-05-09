uniform vec3 lightDir;
varying vec3 normal;

uniform sampler2D Diffuse;
in vec2 TexCoords;
void main()
{
	float intensity;
	vec4 color;
	
	intensity = dot(lightDir,normal);

	if (intensity > 0.95)
		color = vec4(1.0,0.5,0.5,1.0);
	else if (intensity > 0.94)
		color = vec4(0.6,0.3,0.3,1.0);
	else if (intensity > 0.90)
		color = vec4(0.4,0.2,0.2,1.0);
	else
		color = vec4(0.2,0.1,0.1,1.0);
	
	gl_FragColor = texture2D(Diffuse,TexCoords) + color;
}