#version 460 core

out vec4 FragColor;
in vec3 o_color;

// UNIFORMS //
uniform vec3 u_color;


void main()
{
    FragColor = vec4(o_color, 1.0f);
}