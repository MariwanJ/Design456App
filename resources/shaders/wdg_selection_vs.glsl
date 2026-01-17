#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in uint selectionMask;

uniform mat4 mvp;
uniform float pointSize;
flat out uint selectiontype;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    gl_PointSize = pointSize;
    selectiontype = selectionMask;
}
