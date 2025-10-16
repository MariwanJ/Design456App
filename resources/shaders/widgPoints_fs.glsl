#version 460 core

// Widget Vertex Points Fragment Shader

uniform vec4 color;                         // Input color uniform
flat in uint selected;                       // Input from vertex shader (assumed to be uint)
layout(location = 0) out vec4 frag_color;   // Output color to the framebuffer

void main() {
    if (selected != 1) {
        frag_color = color; // Set the fragment color to the input color
    } else {
        frag_color = vec4(1.0, 1.0, 0.0, 1.0); // Set to yellow if selected
    }
}