#version 330 core

in VS_OUT {
    vec3 color; // Outputs color for FS
} vs_out;

out vec4 FragColor;

void main()
{
    FragColor = vec4(vs_out.color, 1.0f);
}