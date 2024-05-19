#shader Vertex
#version 330 core
layout(location = 0) in vec4 position;
out vec4 v_col;
uniform vec4 wallcol;
uniform float depth;
uniform float offsetx;
uniform float offsety;

void main(){

vec4 newpos=position;
newpos.x = position.x + offsetx;
newpos.y = newpos.y /  depth;
newpos.y = newpos.y + offsety;
if(newpos.y>1){
newpos.y=1;
}
gl_Position = newpos;

vec4 newcol=wallcol;
newcol.w = newcol.w * 3 / depth - 0.2f;
if(newcol.w>1){
newcol.w=1;
}
v_col  = newcol;
};

#shader Fragment
#version 330 core
layout(location = 0)out vec4 colour;
out int coltip;
in vec4 v_col;

uniform int coltipe;
void main()
{
    
    if(coltipe==0){
    colour = v_col;
    }else if(coltipe==1){
    colour =vec4(0.05f,0.0f,0.01f,1.0f);
    }else if(coltipe==2){
    colour =vec4(0.0f,0.08f,0.2f,1.0f);
    }   
};
        