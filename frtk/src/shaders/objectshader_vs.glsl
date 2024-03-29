/**
 * objectShader VS
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;


layout (location = 0) out vec3 frag_position;
layout (location = 1) out vec3 frag_normal;
layout (location = 3) out vec4 gl_Position ;

void main () {
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal = normalize(vec3(normalmatrix * vec4(normal, 1.0)));
    gl_Position = mvp * vec4(position, 1.0);
}

