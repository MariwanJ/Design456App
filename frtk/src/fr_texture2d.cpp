#include <../../src/fr_texture2d.h>
#include <../../vendor/stb_image/src/stb_image.h>

/** Default constructor */
Fr_Texture2D::Fr_Texture2D() {
    m_width = 0;
    m_height = 0;
    m_BPP = 0;
    m_LocalBuffer = NULL;
    m_RendererID = -1;
}
bool Fr_Texture2D::set2DTexture(std::string& path, int bpp, int compno) {
    m_FilePath = path;
    m_BPP = bpp;
    numComponents = compno;
    stbi_set_flip_vertically_on_load(1);
    m_LocalBuffer = 0;
    m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_width, &m_height, &m_BPP, numComponents);
    if (m_LocalBuffer == NULL) {
        FRTK_CORE_ERROR("Cannot load Texture", path);
        return false; //nothing to do here
    }
    return true;
}
bool Fr_Texture2D::setup2DTexture() {
    glCheckFunc(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
    glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_width, m_height);
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
    glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    glCheckFunc(glTextureSubImage2D(m_RendererID, 0, 0, 0,  m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));

    if (m_LocalBuffer)
        free(m_LocalBuffer);
    return true;
}
Fr_Texture2D::~Fr_Texture2D()
{
    glDeleteTextures(1, &m_RendererID);
}

void Fr_Texture2D::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE1+slot);
    glBindTextureUnit(slot, m_RendererID);
}

void Fr_Texture2D::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Fr_Texture2D::getTexture()
{
    return m_RendererID;
}
