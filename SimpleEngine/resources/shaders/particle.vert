#version 330 core
layout (location = 0) in vec3 aPos; // Positions/Coordinates
layout (location = 1) in vec2 aTexCoord; // texture positons

out vec2 TexCoords;
out vec4 ParticleColor;

//Transform matrices
uniform mat4 uProj_m = mat4(1.0f);
uniform mat4 uM_m = mat4(1.0f);
uniform mat4 uV_m = mat4(1.0f);

uniform vec3 offset;
uniform vec4 color;

void main()
{
	TexCoords = aTexCoord;
    ParticleColor = color;

    gl_Position = uProj_m * uV_m *  uM_m * vec4(aPos + offset, 1.0);
}