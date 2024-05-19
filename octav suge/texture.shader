#shader Vertex
#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texcoords;
out vec2 v_texcoords;
uniform float offsety;

void main(){
vec4 newpos=position;
newpos.y += offsety;
gl_Position = newpos;
v_texcoords = texcoords;
};

#shader Fragment
#version 330 core
layout(location = 0)out vec4 colour;

in vec2 v_texcoords;
uniform sampler2D u_Texture; 

void main()
{
   vec4 texColor = texture(u_Texture,v_texcoords);
   colour = texColor;
      
};
        