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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#ifndef FR_CONVERTIMAGE_H
#define FR_CONVERTIMAGE_H

#include<fr_core.h>
namespace FR {
    namespace ICONS {
#define HOME                          std::string(EXE_CURRENT_DIR+"/resources/48/home.png")
#define FILE_NEW                      std::string(EXE_CURRENT_DIR+"/resources/48/new.png")
#define FILE_CLOSE                    std::string(EXE_CURRENT_DIR+"/resources/48/close.png")
#define FILE_SAVE                     std::string(EXE_CURRENT_DIR+"/resources/48/save.png")
#define FILE_SAVEAS                   std::string(EXE_CURRENT_DIR+"/resources/48/saveas.png")
#define FILE_IMPORT                   std::string(EXE_CURRENT_DIR+"/resources/48/import.png")
#define FILE_EXPORT                   std::string(EXE_CURRENT_DIR+"/resources/48/export.png")
    }

    class FRTK_API loadImage {
    public:
        /**
         * Class constructor.
         *
         * \param image file name - and path
         */
        loadImage(std::string  image = "");
        std::shared_ptr < unsigned char> getImage(std::string img);
        ~loadImage();

        //Maybe we don't use it?
    private:
        std::string _fName;
    };
}
#endif
