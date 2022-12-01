#version 330 core
layout (location = 0) in vec3 aPos; // Positions/Coordinates
layout (location = 1) in vec3 aCol; // Texture Coordinates

uniform mat4 uProj_m = mat4(1.0f);
uniform mat4 uM_m = mat4(1.0f);
uniform mat4 uV_m = mat4(1.0f);

out VS_OUT {
    vec3 color; // Outputs color for FS
} vs_out;


void main()
{
   
    // Outputs the positions/coordinates of all vertices
    gl_Position = uProj_m * uV_m * uM_m * vec4(aPos, 1.0f);

    vs_out.color = aCol;
}