/**
 * objectShader VS
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 unKnown;  //We send data to here but we dont use it .. why?

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;
uniform mat4 sm_mvp;


layout (location = 0) out vec3 frag_position;
layout (location = 1) out vec3 uTextCoord;
layout (location = 2) out vec3 frag_normal;
layout (location = 3) out vec3 frag_sm_position;
layout (location = 4) out vec4 gl_Position ;

out vec2 v_TexCoord;

void main () {
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal = normalize(vec3(normalmatrix * vec4(normal, 1.0)));
    vec4 sm_position = sm_mvp * vec4(position, 1.0);
    
	frag_sm_position = sm_position.xyz/ sm_position.w;

    gl_Position = mvp * vec4(position, 1.0);
	vec2 uTextCoord= texCoord;
}

