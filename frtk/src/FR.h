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


/** \file
    FR static variable/classes.
 */

#ifndef FR_H
#define FR_H





 /**
	The major release version
  */

#define FR_MAJOR_VERSION        0

  /**
	 The minor release version for this library.
   */
#define FR_MINOR_VERSION        0

   /**
	  The patch version for this library.
	*/
#define FR_PATCH_VERSION        1

#define FR_VERSION      ( (double)FL_MAJOR_VERSION + \
                          (double)FL_MINOR_VERSION * 0.01 + \
                          (double)FL_PATCH_VERSION * 0.0001 )
	// Transparency - No color will be applied

 /* [Color definition used in all widgets consist of
	 a tuple of three float values between 0.0 and 1.0]
 */
struct T {
	float R = 1.0;
	float G = 1.0;
	float B = 1.0;
	float A = 1.0;
};

typedef T FR_COLOR;
namespace COLOR {
#define FR_TRANSPARENCY         =   (-1.0000, -1.0000, -1.0000,  1.0000)		   // No color
#define FR_PINK                 =   ( 1.0000,  0.7529,  0.7961,  1.0000)
#define FR_BLUE                 =   ( 0.0000,  0.0000,  1.0000,  1.0000)
#define FR_BLUEG                =   ( 0.6941,  0.8700,  0.9216,  1.0000)
#define FR_HONEYDEW             =   ( 0.9412,  1.0000,  0.9412,  1.0000)
#define FR_PURPLE               =   ( 0.5020,  0.0000,  0.5020,  1.0000)
#define FR_FUCHSIA              =   ( 1.0000,  0.0000,  1.0000,  1.0000)
#define FR_LAWNGREEN            =   ( 0.4863,  0.9882,  0.0000,  1.0000)
#define FR_AMETHYST             =   ( 0.6000,  0.4000,  0.8000,  1.0000)
#define FR_CRIMSON              =   ( 0.8627,  0.0784,  0.2353,  1.0000)
#define FR_WHITE                =   ( 1.0000,  1.0000,  1.0000,  1.0000)
#define FR_NAVAJOWHITE          =   ( 1.0000,  0.8706,  0.6784,  1.0000)
#define FR_CORNSILK             =   ( 1.0000,  0.9725,  0.8627,  1.0000)
#define FR_BISQUE               =   ( 1.0000,  0.8941,  0.7686,  1.0000)
#define FR_PALEGREEN            =   ( 0.5961,  0.9843,  0.5961,  1.0000)
#define FR_BROWN                =   ( 0.6471,  0.1647,  0.1647,  1.0000)
#define FR_DARKTURQUOISE        =   ( 0.0000,  0.8078,  0.8196,  1.0000)
#define FR_DARKGREEN            =   ( 0.0000,  0.3922,  0.0000,  1.0000)
#define FR_MEDIUMORCHID         =   ( 0.7294,  0.3333,  0.8275,  1.0000)
#define FR_CHOCOLATE            =   ( 0.8235,  0.4118,  0.1176,  1.0000)
#define FR_PAPAYAWHIP           =   ( 1.0000,  0.9373,  0.8353,  1.0000)
#define FR_OLIVE                =   ( 0.5020,  0.5020,  0.0000,  1.0000)
#define FR_SILVER               =   ( 0.7529,  0.7529,  0.7529,  1.0000)
#define FR_PEACHPUFF            =   ( 1.0000,  0.8549,  0.7255,  1.0000)
#define FR_PLUM                 =   ( 0.8667,  0.6275,  0.8667,  1.0000)
#define FR_DARKGOLDENROD        =   ( 0.7216,  0.5255,  0.0431,  1.0000)
#define FR_SLATEGREY            =   ( 0.4392,  0.5020,  0.5647,  1.0000)
#define FR_MINTCREAM            =   ( 0.9608,  1.0000,  0.9804,  1.0000)
#define FR_CORNFLOWERBLUE       =   ( 0.3922,  0.5843,  0.9294,  1.0000)
#define FR_GOLD                 =   ( 1.0000,  0.8431,  0.0000,  1.0000)
#define FR_HOTPINK              =   ( 1.0000,  0.4118,  0.7059,  1.0000)
#define FR_DARKBLUE             =   ( 0.0000,  0.0000,  0.5451,  1.0000)
#define FR_LIMEGREEN            =   ( 0.1961,  0.8039,  0.1961,  1.0000)
#define FR_DEEPSKYBLUE          =   ( 0.0000,  0.7490,  1.0000,  1.0000)
#define FR_DARKKHAKI            =   ( 0.7412,  0.7176,  0.4196,  1.0000)
#define FR_LIGHTGREY            =   ( 0.8275,  0.8275,  0.8275,  1.0000)
#define FR_YELLOW               =   ( 1.0000,  1.0000,  0.0000,  1.0000)
#define FR_GAINSBORO            =   ( 0.8627,  0.8627,  0.8627,  1.0000)
#define FR_MISTYROSE            =   ( 1.0000,  0.8941,  0.8824,  1.0000)
#define FR_SANDYBROWN           =   ( 0.9569,  0.6431,  0.3765,  1.0000)
#define FR_DEEPPINK             =   ( 1.0000,  0.0784,  0.5765,  1.0000)
#define FR_MAGENTA              =   ( 1.0000,  0.0000,  1.0000,  1.0000)
#define FR_ALICEBLUE            =   ( 0.9412,  0.9725,  1.0000,  1.0000)
#define FR_DARKCYAN             =   ( 0.0000,  0.5451,  0.5451,  1.0000)
#define FR_DARKSLATEGREY        =   ( 0.1843,  0.3098,  0.3098,  1.0000)
#define FR_GREENYELLOW          =   ( 0.6784,  1.0000,  0.1843,  1.0000)
#define FR_DARKORCHID           =   ( 0.6000,  0.1961,  0.8000,  1.0000)
#define FR_OLIVEDRAB            =   ( 0.4196,  0.5569,  0.1373,  1.0000)
#define FR_CHARTREUSE           =   ( 0.4980,  1.0000,  0.0000,  1.0000)
#define FR_PERU                 =   ( 0.8039,  0.5216,  0.2471,  1.0000)
#define FR_ORANGE               =   ( 1.0000,  0.6471,  0.0000,  1.0000)
#define FR_RED                  =   ( 1.0000,  0.0000,  0.0000,  1.0000)
#define FR_WHEAT                =   ( 0.9608,  0.8706,  0.7020,  1.0000)
#define FR_LIGHTCYAN            =   ( 0.8784,  1.0000,  1.0000,  1.0000)
#define FR_LIGHTSEAGREEN        =   ( 0.1255,  0.6980,  0.6667,  1.0000)
#define FR_BLUEVIOLET           =   ( 0.5412,  0.1686,  0.8863,  1.0000)
#define FR_LIGHTSLATEGREY       =   ( 0.4667,  0.5333,  0.6000,  1.0000)
#define FR_CYAN                 =   ( 0.0000,  1.0000,  1.0000,  1.0000)
#define FR_MEDIUMPURPLE         =   ( 0.5765,  0.4392,  0.8588,  1.0000)
#define FR_MIDNIGHTBLUE         =   ( 0.0980,  0.0980,  0.4392,  1.0000)
#define FR_FIREBRICK            =   ( 0.6980,  0.1333,  0.1333,  1.0000)
#define FR_PALETURQUOISE        =   ( 0.6863,  0.9333,  0.9333,  1.0000)
#define FR_PALEGOLDENROD        =   ( 0.9333,  0.9098,  0.6667,  1.0000)
#define FR_GRAY                 =   ( 0.5020,  0.5020,  0.5020,  1.0000)
#define FR_MEDIUMSEAGREEN       =   ( 0.2353,  0.7020,  0.4431,  1.0000)
#define FR_MOCCASIN             =   ( 1.0000,  0.8941,  0.7098,  1.0000)
#define FR_IVORY                =   ( 1.0000,  1.0000,  0.9412,  1.0000)
#define FR_DARKSLATEBLUE        =   ( 0.2824,  0.2392,  0.5451,  1.0000)
#define FR_BEIGE                =   ( 0.9608,  0.9608,  0.8627,  1.0000)
#define FR_GREEN                =   ( 0.0000,  0.5020,  0.0000,  1.0000)
#define FR_SLATEBLUE            =   ( 0.4157,  0.3529,  0.8039,  1.0000)
#define FR_TEAL                 =   ( 0.0000,  0.5020,  0.5020,  1.0000)
#define FR_AZURE                =   ( 0.9412,  1.0000,  1.0000,  1.0000)
#define FR_LIGHTSTEELBLUE       =   ( 0.6902,  0.7686,  0.8706,  1.0000)
#define FR_DIMGREY              =   ( 0.4118,  0.4118,  0.4118,  1.0000)
#define FR_TAN                  =   ( 0.8235,  0.7059,  0.5490,  1.0000)
#define FR_ANTIQUEWHITE         =   ( 0.9804,  0.9216,  0.8431,  1.0000)
#define FR_SKYBLUE              =   ( 0.5294,  0.8078,  0.9216,  1.0000)
#define FR_GHOSTWHITE           =   ( 0.9725,  0.9725,  1.0000,  1.0000)
#define FR_MEDIUMTURQUOISE      =   ( 0.2824,  0.8196,  0.8000,  1.0000)
#define FR_FLORALWHITE          =   ( 1.0000,  0.9804,  0.9412,  1.0000)
#define FR_LAVENDERBLUSH        =   ( 1.0000,  0.9412,  0.9608,  1.0000)
#define FR_SEAGREEN             =   ( 0.1804,  0.5451,  0.3412,  1.0000)
#define FR_LAVENDER             =   ( 0.9020,  0.9020,  0.9804,  1.0000)
#define FR_BLANCHEDALMOND       =   ( 1.0000,  0.9216,  0.8039,  1.0000)
#define FR_DARKOLIVEGREEN       =   ( 0.3333,  0.4196,  0.1843,  1.0000)
#define FR_DARKSEAGREEN         =   ( 0.5608,  0.7373,  0.5608,  1.0000)
#define FR_SPRINGGREEN          =   ( 0.0000,  1.0000,  0.4980,  1.0000)
#define FR_NAVY                 =   ( 0.0000,  0.0000,  0.5020,  1.0000)
#define FR_ORCHID               =   ( 0.8549,  0.4392,  0.8392,  1.0000)
#define FR_SADDLEBROWN          =   ( 0.5451,  0.2706,  0.0745,  1.0000)
#define FR_INDIANRED            =   ( 0.8039,  0.3608,  0.3608,  1.0000)
#define FR_SNOW                 =   ( 1.0000,  0.9804,  0.9804,  1.0000)
#define FR_STEELBLUE            =   ( 0.2745,  0.5098,  0.7059,  1.0000)
#define FR_MEDIUMSLATEBLUE      =   ( 0.4824,  0.4078,  0.9333,  1.0000)
#define FR_BLACK                =   ( 0.0000,  0.0000,  0.0000,  1.0000)
#define FR_LIGHTBLUE            =   ( 0.6784,  0.8471,  0.9020,  1.0000)
#define FR_TURQUOISE            =   ( 0.2510,  0.8784,  0.8157,  1.0000)
#define FR_MEDIUMVIOLETRED      =   ( 0.7804,  0.0824,  0.5216,  1.0000)
#define FR_DARKVIOLET           =   ( 0.5804,  0.0000,  0.8275,  1.0000)
#define FR_DARKGRAY             =   ( 0.6627,  0.6627,  0.6627,  1.0000)
#define FR_SECIAL_GRAY          =   ( 0.9101,  0.9101,  0.9101,  1.0000)
#define FR_SALMON               =   ( 0.9804,  0.5020,  0.4471,  1.0000)
#define FR_DARKMAGENTA          =   ( 0.5451,  0.0000,  0.5451,  1.0000)
#define FR_TOMATO               =   ( 1.0000,  0.3882,  0.2784,  1.0000)
#define FR_WHITESMOKE           =   ( 0.9608,  0.9608,  0.9608,  1.0000)
#define FR_GOLDENROD            =   ( 0.8549,  0.6471,  0.1255,  1.0000)
#define FR_MEDIUMSPRINGGREEN    =   ( 0.0000,  0.9804,  0.6039,  1.0000)
#define FR_DODGERBLUE           =   ( 0.1176,  0.5647,  1.0000,  1.0000)
#define FR_AQUA                 =   ( 0.0000,  1.0000,  1.0000,  1.0000)
#define FR_FORESTGREEN          =   ( 0.1333,  0.5451,  0.1333,  1.0000)
#define FR_LEMONCHIFFON         =   ( 1.0000,  0.9804,  0.8039,  1.0000)
#define FR_LIGHTSLATEGRAY       =   ( 0.4667,  0.5333,  0.6000,  1.0000)
#define FR_SLATEGRAY            =   ( 0.4392,  0.5020,  0.5647,  1.0000)
#define FR_LIGHTGRAY            =   ( 0.8275,  0.8275,  0.8275,  1.0000)
#define FR_INDIGO               =   ( 0.2941,  0.0000,  0.5098,  1.0000)
#define FR_CADETBLUE            =   ( 0.3725,  0.6196,  0.6275,  1.0000)
#define FR_LIGHTYELLOW          =   ( 1.0000,  1.0000,  0.8784,  1.0000)
#define FR_DARKORANGE           =   ( 1.0000,  0.5490,  0.0000,  1.0000)
#define FR_POWDERBLUE           =   ( 0.6902,  0.8784,  0.9020,  1.0000)
#define FR_ROYALBLUE            =   ( 0.2549,  0.4118,  0.8824,  1.0000)
#define FR_SIENNA               =   ( 0.6275,  0.3216,  0.1765,  1.0000)
#define FR_THISTLE              =   ( 0.8471,  0.7490,  0.8471,  1.0000)
#define FR_LIME                 =   ( 0.0000,  1.0000,  0.0000,  1.0000)
#define FR_SEASHELL             =   ( 1.0000,  0.9608,  0.9333,  1.0000)
#define FR_DARKRED              =   ( 0.5451,  0.0000,  0.0000,  1.0000)
#define FR_LIGHTSKYBLUE         =   ( 0.5294,  0.8078,  0.9804,  1.0000)
#define FR_SPECIAL_BLUE         =   ( 0.7421,  0.8828,  0.9218,  1.0000)            //Default grid color
#define FR_YELLOWGREEN          =   ( 0.6039,  0.8039,  0.1961,  1.0000)
#define FR_AQUAMARINE           =   ( 0.4980,  1.0000,  0.8314,  1.0000)
#define FR_LIGHTCORAL           =   ( 0.9412,  0.5020,  0.5020,  1.0000)
#define FR_DARKSLATEGRAY        =   ( 0.1843,  0.3098,  0.3098,  1.0000)
#define FR_KHAKI                =   ( 0.9412,  0.9020,  0.5490,  1.0000)
#define FR_DARKGREY             =   ( 0.6627,  0.6627,  0.6627,  1.0000)
#define FR_BURLYWOOD            =   ( 0.8706,  0.7216,  0.5294,  1.0000)
#define FR_LIGHTGOLDENRODYELLOW =   ( 0.9804,  0.9804,  0.8235,  1.0000)
#define FR_MEDIUMBLUE           =   ( 0.0000,  0.0000,  0.8039,  1.0000)
#define FR_DARKSALMON           =   ( 0.9137,  0.5882,  0.4784,  1.0000)
#define FR_ROSYBROWN            =   ( 0.7373,  0.5608,  0.5608,  1.0000)
#define FR_LIGHTSALMON          =   ( 1.0000,  0.6275,  0.4784,  1.0000)
#define FR_PALEVIOLETRED        =   ( 0.8588,  0.4392,  0.5765,  1.0000)
#define FR_CORAL                =   ( 1.0000,  0.4980,  0.3137,  1.0000)
#define FR_VIOLET               =   ( 0.9333,  0.5098,  0.9333,  1.0000)
#define FR_GREY                 =   ( 0.5020,  0.5020,  0.5020,  1.0000)
#define FR_LIGHTGREEN           =   ( 0.5647,  0.9333,  0.5647,  1.0000)
#define FR_LINEN                =   ( 0.9804,  0.9412,  0.9020,  1.0000)
#define FR_ORANGERED            =   ( 1.0000,  0.2706,  0.0000,  1.0000)
#define FR_DIMGRAY              =   ( 0.4118,  0.4118,  0.4118,  1.0000)
#define FR_MAROON               =   ( 0.5020,  0.0000,  0.0000,  1.0000)
#define FR_LIGHTPINK            =   ( 1.0000,  0.7137,  0.7569,  1.0000)
#define FR_MEDIUMAQUAMARINE     =   ( 0.4000,  0.8039,  0.6667,  1.0000)
#define FR_OLDLACE              =   ( 0.9922,  0.9608,  0.9020,  1.0000)
#define FR_GLASS                =   ( 0.3300,  1.0000,  1.0000,  1.0000)
};

#include<fr_callbacks.h>

class FR {
	FR() {}; //NO need for a constructor.
public:
	//static variables used for mouse events inside fgwl.
	static int glfw_e_x;  //SAVE X AND Y OF LAST CLICK INSIDE GLFW
	static int glfw_e_y;
	static int glfw_click;
	static int glfw_double_click;
	
	//Avoid running GLFW OR GLAD CODE whiel GLFW is not created
	static bool s_GLFWInitialized;
	static bool s_GladInitialized;
};



enum {

	GLFW_WINDOW_CLOSE,
	GLFW_WINDOW_RESIZE,
	GLFW_FOCUSE,
	GLFW_APP_RENDER,
	GLFW_KEY_PRESSED,
	GLFW_KEY_RELEASED,
	GLFW_KEY_TYPED,
	
	//MOUSE
	GLFW_MOUSE_LEFT_PUSH,
	GLFW_MOUSE_RIGHT_PUSH,
	GLFW_MOUSE_LEFT_RELEASE,
	GLFW_MOUSE_RIGHT_RELEASE,
	GLFW_MOUSE_MIDDLE_PUSH,
	GLFW_MOUSE_MIDDLE_RELEASE,
	GLFW_MOUSE_DOUBLE_CLICK,   //ONE CLICK IS JUST PUSH
	
	GLFW_MOUSE_MOVE,
	GLFW_MOUSE_SCROLL,


};

#endif // !FR_H
