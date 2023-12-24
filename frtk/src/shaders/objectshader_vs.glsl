
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;
uniform int has_texture;
uniform vec4 vcolor;

layout (location = 0) out vec3 frag_position;
layout (location = 1) out vec3 frag_normal;
layout (location = 2) out vec2 vTextCoord;
layout (location = 3) out vec4 gl_Position ;
layout (location = 4) out int hasTexture ;

void main () {
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal = normalize(vec3(normalmatrix * vec4(normal, 1.0)));
    gl_Position = mvp * vec4(position, 1.0);
	hasTexture=has_texture;
	vTextCoord=texCoord;
}

