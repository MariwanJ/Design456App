#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

class vertexBuffer {

public:
    vertexBuffer(const void *values, GLuint sizeInByte);
    ~vertexBuffer();

    void bindBuffer() const;
    void RemoveBinding() const;

private:
    GLuint renderID;
};

#endif // !VERTEXBUFFER_H
