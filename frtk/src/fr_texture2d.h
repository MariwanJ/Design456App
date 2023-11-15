#ifndef FR_TEXTURE2D_H
#define FR_TEXTURE2D_H

#include<Fr_Core.h>
#include<../../src/fr_node.h>
class Fr_Texture2D {

public:
    Fr_Texture2D();
    ~Fr_Texture2D();
    bool setup2DTexture(std::string& path, int width, int height, int bpp, int compno);
    void Bind(unsigned int slot=0);
    void Unbind();

    inline int getWidth() const { return m_width; };
    inline int getHgeith() const { return m_height; };
private:
    unsigned int m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_width, m_height, m_BPP, numComponents;
    bool active_;
};

#endif
