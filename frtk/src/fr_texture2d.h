//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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

#ifndef FR_TEXTURE2D_H
#define FR_TEXTURE2D_H
#include <frtk.h>

namespace FR {
    class Fr_Texture2D {
    public:
        Fr_Texture2D();
        bool set2DTexture(std::string path = "");
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
}
#endif
