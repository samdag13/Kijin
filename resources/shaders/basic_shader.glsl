#shader vertex
#version 330 core 

layout(location = 0) in vec4 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec4 v_color;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main() 
{ 
	gl_Position = u_MVP * aPosition; 
	v_color = aColor;
	v_TexCoord = aTexCoord;
};


#shader fragment
#version 330 core


layout(location = 0) out vec4 color; 

in vec4 v_color;
in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void main() 
{ 
	vec4 frag_color = texture(u_Texture, v_TexCoord);
	color = frag_color * v_color; 
};