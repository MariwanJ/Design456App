#version 460 core

// Widget Face/Edge/Vertex  Fragment Shader



flat in uint selectiontype;
uniform vec4 baseColor;
uniform vec4 vertexSelectColor;
uniform vec4 edgeSelectColor;
uniform vec4 faceSelectColor;

layout(location = 0) out vec4 frag_color;

void main()
{
    if (selectiontype == 1)  {
        frag_color = faceSelectColor;
    }
    else if (selectiontype == 2) {
        frag_color = edgeSelectColor;
    }
    else if (selectiontype == 3) {
        frag_color = vertexSelectColor;
    }
    else {
        frag_color = baseColor;
    }
}
