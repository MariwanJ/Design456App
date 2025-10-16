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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
// This class is based on the manual https://libgd.github.io/manuals/2.3.0
//

#include <fr_icons.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fr_core.h>
namespace FR {
    loadImage::loadImage(std::string fName) :_fName(fName)
    {
    }

    std::shared_ptr < unsigned char> loadImage::getImage(std::string img) {
        int width, height, channels;
        // unsigned char* imgg = stbi_load(EXE_CURRENT_DIR + "/resources/48/home.png", &width, &height, &channels, 0);
        unsigned char* imgg = stbi_load(std::string(EXE_CURRENT_DIR+"/resources/48/home.png").c_str(), &width, &height, &channels, 0);
        if (imgg == NULL) {
            printf("Error in loading the image\n");
            exit(1);
        }
        return ((std::shared_ptr<unsigned char>)imgg);
    }
    loadImage::~loadImage()
    {
    }
}