#version 420 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

struct DirLight {
    vec4 direction;	
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

struct PointLight {
    vec4 position;	

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;	
	
    float constant;
    float linear;
    float quadratic;
	float padding;
};

struct SpotLight {
    vec4 position;
    vec4 direction;

	vec4 ambient;
    vec4 diffuse;
    vec4 specular;  

    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic; 
	
	float padding1;
	float padding2;
	float padding3;
};

#define MAX_DIR_LIGHTS 100
#define MAX_POINT_LIGHTS 100
#define MAX_SPOT_LIGHTS 100

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
layout (std140, binding = 1) uniform DirLights
{
    DirLight dirlights[MAX_DIR_LIGHTS];
	int numDirLights;
};
layout (std140, binding = 2) uniform PointLights
{
    PointLight pointLights[MAX_POINT_LIGHTS];
	int numPointLights;
};
layout (std140, binding = 3) uniform SpotLights
{
    SpotLight spotLights[MAX_SPOT_LIGHTS];
	int numSpotLights;
};
uniform SpotLight spotLight;
uniform Material material;

// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{    
	//if(texture(material.diffuse, TexCoords).a < 0.001)
	//{
		//discard;
	//}
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    
    // == =====================================================
    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
    // For each phase, a calculate function is defined that calculates the corresponding color
    // per lamp. In the main() function we take all the calculated colors and sum them up for
    // this fragment's final color.
    // == =====================================================
    // phase 1: directional lighting
	vec3 result = vec3(0,0,0);
	for(int i = 0; i < numDirLights; i++)
	{
	    result += CalcDirLight(dirlights[0], norm, viewDir);
	}
    // phase 2: point lights
    for(int i = 0; i < numPointLights; i++)
	{
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    
	}
    // phase 3: spot light
	for(int i = 0; i < numSpotLights; i++)
	{
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);    
	}
    FragColor = vec4(result, texture(material.diffuse, TexCoords).a);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction.xyz);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient.xyz * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse.xyz * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular.xyz * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));   
    // combine results
    vec3 ambient = light.ambient.xyz * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse.xyz * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular.xyz * spec * vec3(texture(material.specular, TexCoords));
	float c = light.constant;
	float d = 0.5 / float(c);
    ambient *= attenuation;
    diffuse *= attenuation ;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position.xyz - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position.xyz - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction.xyz)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient.xyz * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse.xyz * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular.xyz * spec * vec3(texture(material.specular, TexCoords));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}