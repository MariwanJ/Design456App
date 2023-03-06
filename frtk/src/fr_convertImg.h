//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2023
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

#include <../vendor/stb_image/src/stb_image.h>
#include<../vendor/libgd/src/gd.h>

#include<frtk.h>

class loadImage {

public:
    /**
     * Class constructor.
     * 
     * \param image file name - and path
     */
    loadImage(std::string  image="");
    loadImage(); //default constructor
    ~loadImage();
    /**
     * Load XPM Image.
     * 
     * \param filename  File name and path 
     * \return libgd image format  
     */
    std::shared_ptr<gdImagePtr> LoadXPM_F(char* filename);
    
    /**
     * Load XPM image from a string.
     * 
     * \param xpmData String represent the image. Useful if 
     *  you include xpm files (for ex. icons) inside one file
     * \return libgd image format 
     */
    std::shared_ptr<gdImagePtr> LoadXPM_T(std::string xpmData);

    /**
     * Load GIF image .
     * 
     * \param filename file name and path
     * \return libgd image format  
     */
    std::shared_ptr<gdImagePtr> LoadGIF(char* filename);

    /**
     * Load XBM image .
     * 
     * \param filename file name and path
     * \return  libgd image format 
     */
    std::shared_ptr<gdImagePtr> LoadXBM(char* filename);
    /**
     * Load png image.
     * 
     * \param filename file name and path
     * \return 
     */
    std::shared_ptr<gdImagePtr> LoadPng(char* filename);

    /**
     * Save lbgd imaege to png format.
     * 
     * \param FName File name to save the image
     * \param im libgd image format 
     */
    void SavePng(char* FName, gdImagePtr im);
    /**
     * Save libgd image to jpg format.
     * 
     * \param FName file name and path to save the image
     */
    void SaveJpg(char* FName, gdImagePtr im);

    /**
     * Save libgd image format to gif.
     * 
     * \param FName  file name and path to save image
     * \param im
     */
    void SaveGif(char* FName, gdImagePtr im);

//Maybe we don't use it? 
private:
    std::string _fName;
};

#endif
