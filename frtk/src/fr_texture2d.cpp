//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <../../src/fr_texture2d.h>
#include <../../vendor/stb_image/src/stb_image.h>
#include <fr_core.h>

namespace FR {
    /** Default constructor */
    Fr_Texture2D::Fr_Texture2D() {
        m_width = 0;
        m_height = 0;
        m_BPP = 0;
        m_LocalBuffer = nullptr;
        m_RendererID = 0;
    }
    bool Fr_Texture2D::set2DTexture(std::string path) {

        m_FilePath = path;
        m_BPP = 0;
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = 0;
        if (m_FilePath.size() == 0) {
            m_FilePath = EXE_CURRENT_DIR+"/resources/Texture/default.png";    ///Default texture
        }
        
        m_LocalBuffer = stbi_load( m_FilePath.c_str(), &m_width, &m_height, &m_BPP, 4);
        m_BPP = 4;

        if (m_LocalBuffer == NULL) {
            FRTK_CORE_ERROR("Cannot load Texture", path);
            return false; //nothing to do here
        }
        return true;
    }
    bool Fr_Texture2D::setup2DTexture()
    {
        if (m_RendererID != 0)
            return true;

        if (!m_LocalBuffer)
            set2DTexture(m_FilePath);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);

        GLenum internalFormat = GL_RGBA8;
        GLenum format = GL_RGBA;

        int levels = 1 + (int)floor(log2((double)glm::max(m_width, m_height)));

        glTextureStorage2D(m_RendererID, levels, internalFormat, m_width, m_height);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        glTextureSubImage2D(
            m_RendererID,
            0,
            0, 0,
            m_width, m_height,
            format,
            GL_UNSIGNED_BYTE,
            m_LocalBuffer
        );

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);   // <<< ADDED

        glGenerateTextureMipmap(m_RendererID);

        stbi_image_free(m_LocalBuffer);
        m_LocalBuffer = nullptr;

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
        glBindTextureUnit(0, 0);
    }

    uint32_t Fr_Texture2D::getTexture()
    {
        return m_RendererID;
    }
}