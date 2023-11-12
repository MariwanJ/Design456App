/**
 * Texture 
 * Mariwan Jalal
 */

#version 430 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

layout (location = 0) out vec2 v_TexCoord;

uniform mat4 mvp;
uniform vec2 v_Texture;


void main () {
	v_TexCoord=texCoord;
	gl_Position= mvp * vec4(position, 1.0);
}

