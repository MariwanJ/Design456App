/**
 * objectShader FS
 * PUC-Rio 2015.2
 * INF1339 - Computação Gráfica Tridimensional
 * Professor: Waldemar Celes
 * Gabriel de Quadros Ligneul 1212560
 * Trabalho - Projeto Final
 */

#version 460 core



layout (location=0) in vec2 vTextCoord;

uniform sampler2D ourTexture;
uniform vec4 color;


layout (location=0) out vec4 frag_color;



void main ()
{
	frag_color=vec4((color * texture2D(ourTexture,vTextCoord)).rgb, 1.0);
}