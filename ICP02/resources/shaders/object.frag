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
uniform SpotLight spotLights[2];

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

    vec3 light = vec3(0.0f);
    for(int i = 0; i < pointLights.length(); i++)
        light += CalcPointLight(pointLights[i], norm, FragPos , cameraDir);

    for(int i = 0; i < spotLights.length(); i++)
		light += CalcSpotLight(spotLights[i], norm, FragPos , cameraDir);

    vec4 tex = texture(tex0, TexCoords);

    FragColor = tex + vec4(light, 0.0f);
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
	vec3 reflectDir = reflect(-lightDir, normal); //Calucalte direction of reflection 

    // attenuation 
    float lightDistance = length(light.position - fragPos);
    float constAtt = light.constantAttenuation;
    float linAtt = light.linearAttenuation * lightDistance;
    float quadAtt = light.quadraticAttenuation * (lightDistance * lightDistance);
    float attenuation = 1.0 / (constAtt + linAtt + quadAtt);
	
    // colors
    vec3 ambient = light.ambientColor * vec3(1.0); // Ambient light of color
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.diffuseColor; // Diffuse (rozptyl) light determines the
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), 5.0f) * light.specularColor; // Exponent determines "shines"
	
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
    float constAtt = light.constantAttenuation;
    float linAtt = light.linearAttenuation * lightDistance;
    float quadAtt = light.quadraticAttenuation * (lightDistance * lightDistance);
    float attenuation = 1.0 / (constAtt + linAtt + quadAtt);
	
    // colors
    vec3 ambient = light.ambientColor * vec3(1.0);
    vec3 diffuse = max(dot(normal, lightDir), 0.0) * light.diffuseColor;
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), 5.0f) * light.specularColor;

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); // This angel is used to determinant if the fragment is inside the spotlights cone
    float epsilon = light.cutOff - light.outerCutOff; //Eepsilon is the difference between the inner and outer cone angles (ie. the spotlight's cone) 
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); // Intesity is calculated so there is soft transition between inner (full intesitiy) and outer cone (no intensity)
	
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}
