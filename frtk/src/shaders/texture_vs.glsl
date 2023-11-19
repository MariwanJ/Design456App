/**
 * Texture 
 * Mariwan Jalal
 */

#version 430 core
//in
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
uniform mat4 modelview;
uniform vec2 u_Texture;

//out
out vec2 v_TexCoord;
out vec4 oColor;

void main () {
	v_TexCoord=u_Texture;
	oColor = color;
	gl_Position= modelview * vec4(position, 1.0);
}