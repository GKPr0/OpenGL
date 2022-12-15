#version 330 core
layout (location = 0) in vec3 aPos; // Positions/Coordinates
layout (location = 1) in vec2 texPos; // texture positons
layout (location = 2) in vec3 normal; 

//Transform matrices
uniform mat4 uProj_m = mat4(1.0f);
uniform mat4 uM_m = mat4(1.0f);
uniform mat4 uV_m = mat4(1.0f);

//Light properties
uniform vec3 lightPositon = vec3(0.0f);

// Outputs to the fragment shader
out VS_OUT
{
 vec3 N;
 vec3 L;
 vec3 V;
} vs_out;

void main()
{
    // Create Model-View matrix
     mat4 mv_m = uV_m * uM_m;

     // Calculate view-space coordinate - in P point we are computing the color
     vec4 P = mv_m * vec4(aPos, 1.0f);

     // Calculate normal in view space
     vs_out.N = mat3(mv_m) * normal;
     // Calculate view-space light vector
     vs_out.L = lightPositon - P.xyz;
     // Calculate view vector (negative of the view-space position)
     vs_out.V = -P.xyz;

    // Outputs the positions/coordinates of all vertices
    gl_Position = uProj_m * P;
}