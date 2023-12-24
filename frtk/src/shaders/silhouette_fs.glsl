#version 460 core

layout (location = 0) out vec4 frag_color;

void main () {
    if (gl_FrontFacing)
       discard;
    else
        frag_color = vec4(0, 0, 0, 1);
}

