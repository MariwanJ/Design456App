#ifndef FR_TEXTURE2D_H
#define FR_TEXTURE2D_H

#include<Fr_Core.h>

class Fr_Texture2D {
public:
    Fr_Texture2D();
    bool set2DTexture(std::string& path,  int bpp, int compno);
    ~Fr_Texture2D();
    bool setup2DTexture();
    void Bind(unsigned int slot = 0);
    void Unbind();

    inline int getWidth() const { return m_width; };
    inline int getHgeith() const { return m_height; };
    uint32_t getTexture(); //Return the texture 
private:
    uint32_t m_RendererID;
    std::string m_FilePath;
    unsigned char* m_LocalBuffer;
    int m_width, m_height, m_BPP, numComponents; // bpp : Bit per pixel (RGB or RGBA) in the file
};

#endif
