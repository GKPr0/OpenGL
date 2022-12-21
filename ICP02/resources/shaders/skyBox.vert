#version 330 core
layout (location = 0) in vec3 aPos; 

uniform mat4 uProj_m = mat4(1.0f);
uniform mat4 uV_m = mat4(1.0f);
uniform mat4 uM_m = mat4(1.0f);

out vec3 TexCoords;

void main()
{
    TexCoords = aPos;
    gl_Position = uProj_m * uV_m * uM_m * vec4(aPos, 1.0);
}