#version 460 core

out vec4 FragColor;
in vec3 o_color;
in vec2 o_texCoords;

// UNIFORMS //
uniform sampler2D u_texture;
uniform sampler2D u_texture1;

uniform sampler2D Diffuse1;
uniform sampler2D Roughness1;
uniform sampler2D Metallic1;
uniform sampler2D Normal1;


void main()
{
    // FragColor = mix(texture(u_texture, o_texCoords), texture(u_texture1, o_texCoords), 0.2)
    //             * vec4(o_color, 0.0f);
                
    FragColor = texture(Diffuse1, o_texCoords);
}