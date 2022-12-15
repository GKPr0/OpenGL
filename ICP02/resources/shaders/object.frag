#version 330 core

out vec4 FragColor;

// Light properties
uniform vec3 ambientColor = vec3(1.0f);
uniform vec3 diffuseColor = vec3(1.0f);
uniform vec3 specularColor = vec3(1.0f);

uniform float constantAttenuation = 1.0f;
uniform float linearAttenuation = 0.0f;
uniform float quadraticAttenuation = 0.0f;

// Input from vertex shader
in VS_OUT
{
    vec3 N;
    vec3 L;
    vec3 V;
} fs_in;


void main()
{

    // Normalize the incoming N, L and V vectors
    vec3 N = normalize(fs_in.N);
    vec3 L = normalize(fs_in.L);
    vec3 V = normalize(fs_in.V);

    // Calculate R by reflecting -L around the plane defined by N
    vec3 R = reflect(-L, N);

    // Calculate the ambient, diffuse and specular contributions
     vec3 ambient = ambientColor * vec3(1.0);
     vec3 diffuse = max(dot(N, L), 0.0) * diffuseColor;
     vec3 specular = pow(max(dot(R, V), 0.0), 5.0f) * specularColor;
     float lightDistance = length(fs_in.L);
     float distanceAttenuation = 1.0f / (constantAttenuation + linearAttenuation * lightDistance + quadraticAttenuation * lightDistance * lightDistance) ;

    FragColor = vec4(ambient + distanceAttenuation * ( diffuse + specular), 1.0f);
}