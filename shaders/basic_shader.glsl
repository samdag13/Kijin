#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec3 v_texCoord;

uniform mat4 u_MVP;

void main()
{
    gl_position = u_MVP * position;
    v_texCoord = texCoord;
}


#shader fragment
#version 330 core

layout(location = 0) out vec4 out_color;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
    vec4 tex_color = texture(u_texture, v_texCoord);
    color = tex_color;
}