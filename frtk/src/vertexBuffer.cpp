#include <Fr_Core.h>
/**
* Create vertex buffer and bind it
*/
vertexBuffer::vertexBuffer(const void *values, GLuint sizeInByte)
{
    glGenBuffers(1, &renderID);
    glBindBuffer(GL_ARRAY_BUFFER, renderID);
    glBufferData(GL_ARRAY_BUFFER, sizeInByte,values,GL_STATIC_DRAW);
}
/**
*   Delete Buffer
*/
vertexBuffer::~vertexBuffer()
{
    glDeleteBuffers(1, &renderID);
}

/**
* Bind the buffer with the render ID
*/
void vertexBuffer::bindBuffer()const
{
    glBindBuffer(GL_ARRAY_BUFFER, renderID);
}

/**
* Remove the binding with the render ID
*/
void vertexBuffer::RemoveBinding() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}