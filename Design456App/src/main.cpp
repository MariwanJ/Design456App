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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

 const char* idata_test[] = {
"64 64 57 1",
" \tc #C7BFE6",
".\tc #C8BFE6",
"+\tc #CABFE1",
"@\tc #D2B5CE",
"#\tc #D2B5CD",
"$\tc #CEBBD7",
"%\tc #C8BFE3",
"&\tc #E79883",
"*\tc #DEA485",
"=\tc #DEA587",
"-\tc #DEA487",
";\tc #E6986F",
">\tc #D4B4CB",
",\tc #D6B1C5",
"\'\tc #C9BAB2",
")\tc #9AD9EA",
"!\tc #9AD9E9",
"~\tc #A2D6E2",
"{\tc #E39E89",
"]\tc #C7BFE7",
"^\tc #E2A6A9",
"/\tc #A5D3DD",
"(\tc #D4AB9A",
"_\tc #E3A5AA",
":\tc #A2D6E3",
"<\tc #D0AD9E",
"[\tc #C9BEE6",
"}\tc #E3A6A7",
"|\tc #D1AD9D",
"1\tc #C8BFE5",
"2\tc #E3A6A8",
"3\tc #C8BFE4",
"4\tc #99D9EA",
"5\tc #A3D6E3",
"6\tc #9BD8EA",
"7\tc #D0AD9D",
"8\tc #C9BFE5",
"9\tc #DEA9B0",
"0\tc #ADCDD4",
"a\tc #9AD9E8",
"b\tc #DAAA94",
"c\tc #D1B9D5",
"d\tc #DEA288",
"e\tc #A6D3DD",
"f\tc #A5D4DE",
"g\tc #A5D4DF",
"h\tc #A4D4DF",
"i\tc #BBC4C3",
"j\tc #E2A19D",
"k\tc #C7BFE5",
"l\tc #DCACBA",
"m\tc #ED926D",
"n\tc #ED916D",
"o\tc #E99A8D",
"p\tc #CBBCDF",
"q\tc #C7C0E6",
"r\tc #C8BEE4",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                 .+@##########################@$..              ",
"                 %&*==========================-;>               ",
"                 ,\')!!!)!!!!!)!!!!)!!!!!)!!!!)!~{               ",
"                ]^/)))))))))))))))))))))))))))))(.              ",
"                 _:)))))))))))))))))))))))))))))<[              ",
"                 }:)))))))))))))))))))))))))))))|1              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:)))))))))))))))))))))))))))))|3              ",
"                 2:!)))))))))))))))))))))))))))4|1              ",
"                 25))))))))))))))))))))))))))))678              ",
"                ]90!)))))))))))))))))))))))))))ab.              ",
"                .cdeffggggfggggffggggfggggffgghij               ",
"                kklmmmmnmmmmnnmmmmnnmmmmnmmmmnmopq              ",
"                 .k133333333333333333333333333rk1.              ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                ",
"                                                                "
};


#include<Application.h>

#include<../stb_image/src/stb_image.h>
int main(int argc, char** argv)
{
    Application* Design456App = new Application();
    int width, height, original_no_channels;
    int desired_no_channels = 3;
    auto myimage = loadImage();
    
    //unsigned char* img = freeImge("E:/Projects/Design456App/test.xpm", &width, &height, &original_no_channels, desired_no_channels);
    //if (img == NULL) {
    //        printf("Error in loading the image\n");
  //          exit(1);
    //}
    return Design456App->run(argc,argv);
}