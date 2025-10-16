#version 460 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform float silhouette;
uniform mat4 mvp;

void main() {
    vec3 Xnormal = normalize(normal);
    gl_Position = mvp * vec4(position + silhouette * Xnormal, 1.0);
}
