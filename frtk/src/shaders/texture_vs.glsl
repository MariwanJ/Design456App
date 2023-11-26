/**
 * Texture 
 * Mariwan Jalal
 */

#version 460 core


layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

uniform mat4 modelview;

layout (location = 0) out vec2 vTextCoord;
layout (location = 1) out vec4 gl_Position ;

void main () {
    gl_Position =  modelview * vec4(position, 1.0);
	vTextCoord= texCoord;
}

