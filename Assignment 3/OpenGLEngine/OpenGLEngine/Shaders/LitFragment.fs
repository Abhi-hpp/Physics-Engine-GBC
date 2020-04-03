#version 330 core
struct Material {
    sampler2D diffuse;
    sampler2D specular;
	sampler2D emission;
    float shininess;
	float emissive;
}; 

struct Light {
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  
 
uniform Material material;

out vec4 FragColor;
  
uniform vec3 objectColor;

in vec3 Normal;  
in vec3 FragPos; 
in vec3 EyeNormal;
in vec3 EyeFragPos;  
in vec2 TexCoords;

uniform vec3 lightPos;  
uniform vec3 viewPos;
uniform vec3 EyeSpaceLightPos;  


void main()
{    
    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
  	
    // diffuse 
    //vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    //float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = light.diffuse * (diff * material.diffuse);
    
    // specular
    //vec3 viewDir = normalize(viewPos - FragPos);
   // vec3 reflectDir = reflect(-lightDir, EyeNormal);  
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    //vec3 specular = light.specular * (spec * material.specular);  

	// diffuse eye space
    vec3 norm = normalize(EyeNormal);
    vec3 lightDir = normalize(light.position - EyeFragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.diffuse, TexCoords)));

	// specular eye space
    vec3 viewDir = normalize(-EyeFragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.specular, TexCoords)));  

	vec3 emission = vec3(texture(material.emission, TexCoords));  
	if(emission.x < 0.1)
	{
		emission.y = 0;
		emission.z = 0;
	}
        
    vec3 result = ambient + diffuse + specular + material.emissive * emission;
    FragColor = vec4(result, 1.0);
	//FragColor = vec4(EyeFragPos, 1.0);
}