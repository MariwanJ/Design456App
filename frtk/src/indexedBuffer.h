#ifndef INDEXEDBUFFER_H
#define INDEXEDBUFFER_H

class indexedBuffer {

public:
    indexedBuffer(const GLuint*values, GLuint IndiciesCount);
    ~indexedBuffer();

    void bindBuffer() const;
    void RemoveBinding() const;
    GLuint getIndiciesCount()const;
private:
    GLuint renderID;
    GLuint noOfIndicies;  //How many indicies?
};

#endif // !INDEXEDBUFFER_H
