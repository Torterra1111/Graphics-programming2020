#version 330 core
out vec4 Fragcolour;

in vec3 Position; //positions for each vertex
in vec3 Normal; //Surface Normals for each vertex
  
uniform vec3 lightpos; //In the world space
uniform vec3 ViewPosition; //Camera position in world space
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 ViewDir;

void main()
{
    //ambient
	float Ambientlightstr = 0.5f;
	vec3 ambient = Ambientlightstr * lightColor;

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightpos - Position);
	float diffusestr = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diffusestr * lightColor;

	//specular
	float specularStr = 0.5;
	vec3 viewDir = normalize(ViewPosition - Position);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir,reflectDir),0.0),128);
	vec3 specular = specularStr *spec * lightColor;


	//RimShade
	float ShadeRim = 1 - max(dot(Normal,ViewDir),0.0);
	vec3 colour = (vec3(smoothstep(0.0,1.0,ShadeRim)));

	
	//total
	vec3 total = (ambient+diffuse+specular+colour) * (objectColor); //ambient+diffuse+specular+colour
			//float testing = Normal.x+Normal.y+Normal.z; 
		//if (testing > 0.5)
		//total = vec3(1.0,0.0,0.0);
//	else if (testing > 0.75)
	//	total = vec3(0.0,1.0,0.0);
	//else if (testing > 1.5)
	//	total = vec3(0.0,0.2,1.0);
//	else
	//	total = vec3(0.0,0.0,0.0);
	
	Fragcolour = vec4(total, 1.0);
}