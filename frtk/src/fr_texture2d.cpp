#include <../../src/fr_texture2d.h>
#include <../../vendor/stb_image/src/stb_image.h>
namespace FR {
    /** Default constructor */
    Fr_Texture2D::Fr_Texture2D() {
        m_width = 0;
        m_height = 0;
        m_BPP = 0;
        m_LocalBuffer = NULL;
        m_RendererID = -1;
    }
    bool Fr_Texture2D::set2DTexture(std::string path) {
        m_FilePath = path;
        m_BPP = 0;
        numComponents = 0;
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = 0;
        if (m_FilePath.size() == 0) {
            m_FilePath = EXE_CURRENT_DIR+"/resources/Texture/default.png";    ///Default texture
        }
        m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_width, &m_height, &m_BPP, numComponents);
        if (m_LocalBuffer == NULL) {
            FRTK_CORE_ERROR("Cannot load Texture", path);
            return false; //nothing to do here
        }
        return true;
    }
    bool Fr_Texture2D::setup2DTexture() {
        if (m_LocalBuffer == NULL) {
            set2DTexture();
        }
        glCheckFunc(glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID));
        if (m_BPP == 3) {
            glCheckFunc(glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_width, m_height));
        }
        else if (m_BPP == 4) {
            glCheckFunc(glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_width, m_height));
        }
        glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
        glCheckFunc(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
        if (m_BPP == 3) {
            glCheckFunc(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_width, m_height, GL_RGB, GL_UNSIGNED_BYTE, m_LocalBuffer));
        }
        else
            if (m_BPP == 4) {
                glCheckFunc(glTextureSubImage2D(m_RendererID, 0, 0, 0, m_width, m_height, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
            }

        stbi_image_free(m_LocalBuffer);
        return true;
    }
    Fr_Texture2D::~Fr_Texture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void Fr_Texture2D::Bind(unsigned int slot)
    {
        //glCheckFunc(glActiveTexture(GL_TEXTURE0 + slot));
        glCheckFunc(glBindTextureUnit(slot, m_RendererID));
    }

    void Fr_Texture2D::Unbind()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    uint32_t Fr_Texture2D::getTexture()
    {
        return m_RendererID;
    }
}