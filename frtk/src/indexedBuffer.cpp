#include <Fr_Core.h>
/**
* Create vertex buffer and bind it
*/
indexedBuffer::indexedBuffer(const GLuint *values, GLuint IndiciesCount):noOfIndicies(IndiciesCount)
{
    glGenBuffers(1, &renderID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiciesCount*sizeof(GLuint), values, GL_STATIC_DRAW);
}
/**
*   Delete Buffer
*/
indexedBuffer::~indexedBuffer()
{
    glDeleteBuffers(1, &renderID);
}

/**
* Bind the buffer with the render ID
*/
void indexedBuffer::bindBuffer() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
}

/**
* Remove the binding with the render ID
*/
void indexedBuffer::RemoveBinding() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLuint indexedBuffer::getIndiciesCount() const
{
    return noOfIndicies;
}
