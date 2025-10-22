#version 460 core

// Widget Vertex Points Vertex Shader

layout(location = 0) in vec3 position; // Vertex position
layout(location = 1) in vec4 vertexColor; // Vertex color
layout(location = 2) in uint isSelected; // Input for selection status . boolean but we use size_t

uniform mat4 mvp;
uniform float pointSize;  // not sure what to do with this
out uint selected; // Output to fragment shader

void main() {
    gl_Position = mvp * vec4(position, 1.0);
    gl_PointSize = pointSize; // Set the size of the point from uniform
    selected = isSelected; // Pass the selected status to the fragment shader
}