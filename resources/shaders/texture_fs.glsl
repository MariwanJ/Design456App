#version 460 core

layout (location=0) in vec2 vTextCoord;

uniform sampler2D ourTexture;
uniform vec4 color;
uniform int hasTexture;


layout (location=0) out vec4 frag_color;



void main ()
{
	if (hasTexture==1)
		frag_color=vec4((color * texture2D(ourTexture,vTextCoord)).rgb, 1.0);
	else
		frag_color=vec4(color.rgb,1.0) ; //Totally transparency
	
}