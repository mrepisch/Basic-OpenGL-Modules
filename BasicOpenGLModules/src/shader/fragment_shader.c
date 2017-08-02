struct Material
{
	vec3 diffuse;
	vec3 specular;

	sampler2D diffuseTexture;
	sampler2D specularTexture;
	float shininess;
};

struct Light
{
	vec3 direction;	
    vec3 ambient;
    vec3 position;
	vec3 lightColor;
    
    float constant;
    float linear;
    float quadratic;
    
    float cutOff;
    float outerCutOff;
    
    int type;
};


out vec4 FragColor;

in vec3 FragPos;  
in vec3 Normal;  
in vec2 TexCoord;


uniform vec3 viewPos;
uniform Material material;
uniform Light lightsource[20];
uniform int amountOfLights;


vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0);
    for( int i = 0; i < amountOfLights; i++)
    {
		Light light = lightsource[i];
		if( light.type == 0)
		{
			result += CalcDirLight(light,norm, viewDir);
		}
		else if( light.type == 1)
		{
			result += CalcPointLight(light,norm,FragPos,viewDir);
		}
		else if( light.type == 2)
		{
			result += CalcSpotLight(light, norm, FragPos, viewDir);
		}
	}
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(Light light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 diffuse  = material.diffuse  * diff * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 specular = material.specular * spec * vec3(texture(material.specularTexture, TexCoord));
    return (ambient + diffuse + specular);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 diffuse = material.diffuse * diff * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 specular = material.specular * spec * vec3(texture(material.specularTexture, TexCoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(Light light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient = light.ambient * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 diffuse = material.diffuse * diff * vec3(texture(material.diffuseTexture, TexCoord));
    vec3 specular = material.specular * spec * vec3(texture(material.specularTexture, TexCoord));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular);
}
