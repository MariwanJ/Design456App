/**
 * Texture 
 * Mariwan Jalal
 */

#version 430 core

layout (location = 0) out vec4 frag_color;
layout (location =1) in vec2 texCoord; 


void main () {
    vec4 texColor=texture(u_Texture,v_texCoord);
     frag_color = texColor;
}

