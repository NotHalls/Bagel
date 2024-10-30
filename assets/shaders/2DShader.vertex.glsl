#version 460 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec3 a_color;
layout (location = 2) in vec2 a_texCoords;
// layout (location = 3) in vec3 a_normals;

out vec3 o_color;
out vec2 o_texCoords;

// UNIFORMS //
uniform mat4 u_mvp;


void main()
{
    gl_Position = u_mvp * vec4(a_pos, 1.0f);
    // o_color = a_color;
    o_texCoords = a_texCoords;

    // this is used for checking if the texCoords are correct
    // o_color = vec3(a_texCoords, 0.0f);
}