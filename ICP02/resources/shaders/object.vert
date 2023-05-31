#version 330 core
layout (location = 0) in vec3 aPos; // Positions/Coordinates
layout (location = 1) in vec2 aTexCoord; // texture positons
layout (location = 2) in vec3 aNormal; 

//Transform matrices
uniform mat4 uProj_m = mat4(1.0f); // Projection matrix to convert 3D to 2D projection
uniform mat4 uM_m = mat4(1.0f); // Model matrix to convert local to world coordinates
uniform mat4 uV_m = mat4(1.0f); // View matrix to convert world to view coordinates


// Outputs to the fragment shader
out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;


void main()
{
    FragPos = vec3(uM_m * vec4(aPos, 1.0)); // Transforms local point to world point corrdinates
    Normal = mat3(transpose(inverse(uM_m))) * aNormal;  //Correctly transfrom normals even when non-uniformly scaled
    TexCoords = aTexCoord;

    // Outputs the positions/coordinates of all vertices
    gl_Position = uProj_m * uV_m * vec4(FragPos, 1.0); // Point coordinates in clip (camera) space 
}