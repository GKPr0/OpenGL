#version 330 core

in vec2 TexCoords;
in vec4 ParticleColor;

out vec4 FragColor;

// Textures
uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, TexCoords) * ParticleColor;
}  