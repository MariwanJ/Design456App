#shader vertexShaderSource
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
};

#shader fragmentShaderSource
#version 330 core
layout (location=0) out vec4 FragColor;
uniform u_Color;
void main()
{
    FragColor = u_Color;//vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
};

