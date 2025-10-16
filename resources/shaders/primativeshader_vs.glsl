
#version 460 core
//mvbo from 0 to 2 
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 modelview;
uniform mat4 normalmatrix;
uniform mat4 mvp;

layout(location = 0) out vec3 frag_position;
layout(location = 1) out vec3 frag_normal;
layout(location = 2) out vec2 vTextCoord;

void main() {
    frag_position = vec3(modelview * vec4(position, 1.0));
    frag_normal = normalize(vec3(normalmatrix * vec4(normal, 0.0)));
    vTextCoord = texCoord;
    gl_Position = mvp * vec4(position, 1.0);
}
