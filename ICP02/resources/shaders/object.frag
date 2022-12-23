#version 330 core
// For lights see https://learnopengl.com/Lighting/Multiple-lights

out vec4 FragColor;


// Lights definitions
struct PointLight {
    vec3 position;
	
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;
};

struct SpotLight {
    vec3 position;
	vec3 direction;
    float cutOff;
    float outerCutOff;

    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;

    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

    bool isOn;
};


// Camera
uniform vec3 cameraPos;

// Lights
uniform PointLight pointLights[1];
uniform SpotLight spotLights[1];

// Textures
uniform sampler2D tex0; 

// Inputs
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

    vec3 norm = normalize(Normal);
    vec3 cameraDir = normalize(cameraPos - FragPos);

    vec3 light = CalcSpotLight(spotLights[0], norm, FragPos , cameraDir);
    light += CalcPointLight(pointLights[0], norm, FragPos , cameraDir);

    vec4 tex = texture(tex0, TexCoords);

    FragColor = tex + vec4(light,1.0f);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

    // attenuation
    float lightDistance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * lightDistance + light.quadraticAttenuation * (lightDistance * lightDistance));    
	
    // colors
    vec3 ambient = light.ambientColor * vec3(1.0);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.diffuseColor;
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), 5.0f) * light.specularColor;
	
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
	
    return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    if(light.isOn == false)
        return vec3(0.0f);

    vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal);

     // attenuation
    float lightDistance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constantAttenuation + light.linearAttenuation * lightDistance + light.quadraticAttenuation * (lightDistance * lightDistance));    
	
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // colors
    vec3 ambient = light.ambientColor * vec3(1.0);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.diffuseColor;
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), 5.0f) * light.specularColor;
	
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}
