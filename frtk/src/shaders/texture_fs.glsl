/**
 * Texture 
 * Mariwan Jalal
 */

#version 460 core
//in
in vec4 oColor;
vec2 v_TexCoord; 


uniform sampler2D ourTexture;
//out
layout (location = 0) out vec4 frag_color;


void main () {
    frag_color = texture(ourTexture,v_TexCoord);
}