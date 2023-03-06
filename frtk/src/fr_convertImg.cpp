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
// This class is based on the manual https://libgd.github.io/manuals/2.3.0
//

#include <fr_convertImg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

loadImage::loadImage(std::string fName) :_fName(fName)
{
}

loadImage::loadImage()
{
}

loadImage::~loadImage()
{
}

std::shared_ptr <gdImagePtr> loadImage::LoadXPM_F(char* FName) {
    gdImagePtr im;

    im = gdImageCreateFromXpm(FName);
    return std::make_shared<gdImagePtr>(im);
}

std::shared_ptr<gdImagePtr> loadImage::LoadXPM_T(std::string xpmData)
{
    std::ofstream outfile;  
    outfile.open("temp.txt"); // append instead of overwrite
    outfile << xpmData;
    outfile.close();
    return LoadXPM_F("temp.xpm");
}

std::shared_ptr <gdImagePtr> loadImage::LoadGIF(char* FName) {
    gdImagePtr im;
    FILE* in;
    in = fopen(FName, "rb");
    im = gdImageCreateFromGif(in);
    fclose(in);
    return std::make_shared<gdImagePtr>(im);
}
std::shared_ptr <gdImagePtr> loadImage::LoadXBM(char* FName) {
    gdImagePtr im;
    FILE* in;
    in = fopen(FName, "rb");
    im = gdImageCreateFromXbm(in);
    fclose(in);
    return std::make_shared<gdImagePtr>(im);
}

std::shared_ptr<gdImagePtr> loadImage::LoadPng(char* FName)
{
    FILE* in;
    struct stat stat_buf;
    gdImagePtr im;
    in = fopen(FName, "rb");
    if (!in) {
        /* Error */
    }
    if (fstat(fileno(in), &stat_buf) != 0) {
        /* Error */
    }
    /* Read the entire thing into a buffer
      that we allocate */
    char* buffer = (char*)malloc(stat_buf.st_size);
    if (!buffer) {
        /* Error */
    }
    if (fread(buffer, 1, stat_buf.st_size, in) != stat_buf.st_size)
    {
        /* Error */
    }
    im = gdImageCreateFromPngPtr(stat_buf.st_size, buffer);
    /* WE allocated the memory, WE free
      it with our normal free function */
    free(buffer);
    fclose(in);
    return std::make_shared<gdImagePtr>(im);
}

void loadImage::SavePng(char* FName, gdImagePtr im)
{
    FILE* out;
    int size;
    char* data;
    out = fopen(FName, "wb");
    if (!out) {
        /* Error */
    }
    data = (char*)gdImagePngPtr(im, &size);
    if (!data) {
        /* Error */
    }
    if (fwrite(data, 1, size, out) != size) {
        /* Error */
    }
    if (fclose(out) != 0) {
        /* Error */
    }
    gdFree(data);
}

void loadImage::SaveJpg(char* FName, gdImagePtr im) {
    
    int black, white;
    FILE* out;
    // Create the image
    im = gdImageCreate(100, 100);
    // Allocate background
    white = gdImageColorAllocate(im, 255, 255, 255);
    // Allocate drawing color
    black = gdImageColorAllocate(im, 0, 0, 0);
    // Draw rectangle
    gdImageRectangle(im, 0, 0, 99, 99, black);
    // Open output file in binary mode
    out = fopen(FName, "wb");
    // Write JPEG using default quality
    gdImageJpeg(im, out, -1);
    // Close file
    fclose(out);
    // Destroy image
    gdImageDestroy(im);
}
//FIXME - Size shouldn't be fixe
void loadImage::SaveGif(char* FName, gdImagePtr im) {
    int black, white;
    FILE* out;
    // Create the image
    im = gdImageCreate(100, 100);
    // Allocate background
    white = gdImageColorAllocate(im, 255, 255, 255);
    // Allocate drawing color
    black = gdImageColorAllocate(im, 0, 0, 0);
    // Draw rectangle
    gdImageRectangle(im, 0, 0, 99, 99, black);
    // Open output file in binary mode
    out = fopen(FName, "wb");
    // Write GIF
    gdImageGif(im, out);
    // Close file
    fclose(out);
    // Destroy image
    gdImageDestroy(im);
}