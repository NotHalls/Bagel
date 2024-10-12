#version 460 core

out vec4 FragColor;
in vec3 o_color;
in vec2 o_texCoords;

// UNIFORMS //
uniform vec3 u_color;
uniform sampler2D u_texture;
uniform sampler2D u_texture1;

void main()
{
    FragColor = mix(texture(u_texture, o_texCoords), texture(u_texture1, o_texCoords), 0.5f)
                * vec4(o_color, 0.0f);
}