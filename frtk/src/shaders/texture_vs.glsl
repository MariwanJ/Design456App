/**
 * Texture 
 * Mariwan Jalal
 */

#version 430 core

layout(location = 0) in vec3 position;

layout (location = 1) out vec2 v_TexCoord;

uniform mat4 modelview;
uniform vec2 u_Texture;

void main () {
	v_TexCoord=u_Texture;
	gl_Position= mvp * vec4(position, 1.0);
}