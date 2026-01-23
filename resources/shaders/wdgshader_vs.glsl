#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 vTextCoord;

void main()
{
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal   = normalize(mat3(normalmatrix) * normal);
    vTextCoord    = texCoord;
    gl_Position   = mvp * vec4(position, 1.0);
}
