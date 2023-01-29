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
#define FR_TRANSPARENCY         -1.0000f, -1.0000f, -1.0000f,  1.0000f		   // No color
#define FR_PINK                  1.0000f,  0.7529f,  0.7961f,  1.0000f
#define FR_BLUE                  0.0000f,  0.0000f,  1.0000f,  1.0000f
#define FR_BLUEG                 0.6941f,  0.8700f,  0.9216f,  1.0000f
#define FR_HONEYDEW              0.9412f,  1.0000f,  0.9412f,  1.0000f
#define FR_PURPLE                0.5020f,  0.0000f,  0.5020f,  1.0000f
#define FR_FUCHSIA               1.0000f,  0.0000f,  1.0000f,  1.0000f
#define FR_LAWNGREEN             0.4863f,  0.9882f,  0.0000f,  1.0000f
#define FR_AMETHYST              0.6000f,  0.4000f,  0.8000f,  1.0000f
#define FR_CRIMSON               0.8627f,  0.0784f,  0.2353f,  1.0000f
#define FR_WHITE                 1.0000f,  1.0000f,  1.0000f,  1.0000f
#define FR_NAVAJOWHITE           1.0000f,  0.8706f,  0.6784f,  1.0000f
#define FR_CORNSILK              1.0000f,  0.9725f,  0.8627f,  1.0000f
#define FR_BISQUE                1.0000f,  0.8941f,  0.7686f,  1.0000f
#define FR_PALEGREEN             0.5961f,  0.9843f,  0.5961f,  1.0000f
#define FR_BROWN                 0.6471f,  0.1647f,  0.1647f,  1.0000f
#define FR_DARKTURQUOISE         0.0000f,  0.8078f,  0.8196f,  1.0000f
#define FR_DARKGREEN             0.0000f,  0.3922f,  0.0000f,  1.0000f
#define FR_MEDIUMORCHID          0.7294f,  0.3333f,  0.8275f,  1.0000f
#define FR_CHOCOLATE             0.8235f,  0.4118f,  0.1176f,  1.0000f
#define FR_PAPAYAWHIP            1.0000f,  0.9373f,  0.8353f,  1.0000f
#define FR_OLIVE                 0.5020f,  0.5020f,  0.0000f,  1.0000f
#define FR_SILVER                0.7529f,  0.7529f,  0.7529f,  1.0000f
#define FR_PEACHPUFF             1.0000f,  0.8549f,  0.7255f,  1.0000f
#define FR_PLUM                  0.8667f,  0.6275f,  0.8667f,  1.0000f
#define FR_DARKGOLDENROD         0.7216f,  0.5255f,  0.0431f,  1.0000f
#define FR_SLATEGREY             0.4392f,  0.5020f,  0.5647f,  1.0000f
#define FR_MINTCREAM             0.9608f,  1.0000f,  0.9804f,  1.0000f
#define FR_CORNFLOWERBLUE        0.3922f,  0.5843f,  0.9294f,  1.0000f
#define FR_GOLD                  1.0000f,  0.8431f,  0.0000f,  1.0000f
#define FR_HOTPINK               1.0000f,  0.4118f,  0.7059f,  1.0000f
#define FR_DARKBLUE              0.0000f,  0.0000f,  0.5451f,  1.0000f
#define FR_LIMEGREEN             0.1961f,  0.8039f,  0.1961f,  1.0000f
#define FR_DEEPSKYBLUE           0.0000f,  0.7490f,  1.0000f,  1.0000f
#define FR_DARKKHAKI             0.7412f,  0.7176f,  0.4196f,  1.0000f
#define FR_LIGHTGREY             0.8275f,  0.8275f,  0.8275f,  1.0000f
#define FR_YELLOW                1.0000f,  1.0000f,  0.0000f,  1.0000f
#define FR_GAINSBORO             0.8627f,  0.8627f,  0.8627f,  1.0000f
#define FR_MISTYROSE             1.0000f,  0.8941f,  0.8824f,  1.0000f
#define FR_SANDYBROWN            0.9569f,  0.6431f,  0.3765f,  1.0000f
#define FR_DEEPPINK              1.0000f,  0.0784f,  0.5765f,  1.0000f
#define FR_MAGENTA               1.0000f,  0.0000f,  1.0000f,  1.0000f
#define FR_ALICEBLUE             0.9412f,  0.9725f,  1.0000f,  1.0000f
#define FR_DARKCYAN              0.0000f,  0.5451f,  0.5451f,  1.0000f
#define FR_DARKSLATEGREY         0.1843f,  0.3098f,  0.3098f,  1.0000f
#define FR_GREENYELLOW           0.6784f,  1.0000f,  0.1843f,  1.0000f
#define FR_DARKORCHID            0.6000f,  0.1961f,  0.8000f,  1.0000f
#define FR_OLIVEDRAB             0.4196f,  0.5569f,  0.1373f,  1.0000f
#define FR_CHARTREUSE            0.4980f,  1.0000f,  0.0000f,  1.0000f
#define FR_PERU                  0.8039f,  0.5216f,  0.2471f,  1.0000f
#define FR_ORANGE                1.0000f,  0.6471f,  0.0000f,  1.0000f
#define FR_RED                   1.0000f,  0.0000f,  0.0000f,  1.0000f
#define FR_WHEAT                 0.9608f,  0.8706f,  0.7020f,  1.0000f
#define FR_LIGHTCYAN             0.8784f,  1.0000f,  1.0000f,  1.0000f
#define FR_LIGHTSEAGREEN         0.1255f,  0.6980f,  0.6667f,  1.0000f
#define FR_BLUEVIOLET            0.5412f,  0.1686f,  0.8863f,  1.0000f
#define FR_LIGHTSLATEGREY        0.4667f,  0.5333f,  0.6000f,  1.0000f
#define FR_CYAN                  0.0000f,  1.0000f,  1.0000f,  1.0000f
#define FR_MEDIUMPURPLE          0.5765f,  0.4392f,  0.8588f,  1.0000f
#define FR_MIDNIGHTBLUE          0.0980f,  0.0980f,  0.4392f,  1.0000f
#define FR_FIREBRICK             0.6980f,  0.1333f,  0.1333f,  1.0000f
#define FR_PALETURQUOISE         0.6863f,  0.9333f,  0.9333f,  1.0000f
#define FR_PALEGOLDENROD         0.9333f,  0.9098f,  0.6667f,  1.0000f
#define FR_GRAY                  0.5020f,  0.5020f,  0.5020f,  1.0000f
#define FR_MEDIUMSEAGREEN        0.2353f,  0.7020f,  0.4431f,  1.0000f
#define FR_MOCCASIN              1.0000f,  0.8941f,  0.7098f,  1.0000f
#define FR_IVORY                 1.0000f,  1.0000f,  0.9412f,  1.0000f
#define FR_DARKSLATEBLUE         0.2824f,  0.2392f,  0.5451f,  1.0000f
#define FR_BEIGE                 0.9608f,  0.9608f,  0.8627f,  1.0000f
#define FR_GREEN                 0.0000f,  0.5020f,  0.0000f,  1.0000f
#define FR_SLATEBLUE             0.4157f,  0.3529f,  0.8039f,  1.0000f
#define FR_TEAL                  0.0000f,  0.5020f,  0.5020f,  1.0000f
#define FR_AZURE                 0.9412f,  1.0000f,  1.0000f,  1.0000f
#define FR_LIGHTSTEELBLUE        0.6902f,  0.7686f,  0.8706f,  1.0000f
#define FR_DIMGREY               0.4118f,  0.4118f,  0.4118f,  1.0000f
#define FR_TAN                   0.8235f,  0.7059f,  0.5490f,  1.0000f
#define FR_ANTIQUEWHITE          0.9804f,  0.9216f,  0.8431f,  1.0000f
#define FR_SKYBLUE               0.5294f,  0.8078f,  0.9216f,  1.0000f
#define FR_GHOSTWHITE            0.9725f,  0.9725f,  1.0000f,  1.0000f
#define FR_MEDIUMTURQUOISE       0.2824f,  0.8196f,  0.8000f,  1.0000f
#define FR_FLORALWHITE           1.0000f,  0.9804f,  0.9412f,  1.0000f
#define FR_LAVENDERBLUSH         1.0000f,  0.9412f,  0.9608f,  1.0000f
#define FR_SEAGREEN              0.1804f,  0.5451f,  0.3412f,  1.0000f
#define FR_LAVENDER              0.9020f,  0.9020f,  0.9804f,  1.0000f
#define FR_BLANCHEDALMOND        1.0000f,  0.9216f,  0.8039f,  1.0000f
#define FR_DARKOLIVEGREEN        0.3333f,  0.4196f,  0.1843f,  1.0000f
#define FR_DARKSEAGREEN          0.5608f,  0.7373f,  0.5608f,  1.0000f
#define FR_SPRINGGREEN           0.0000f,  1.0000f,  0.4980f,  1.0000f
#define FR_NAVY                  0.0000f,  0.0000f,  0.5020f,  1.0000f
#define FR_ORCHID                0.8549f,  0.4392f,  0.8392f,  1.0000f
#define FR_SADDLEBROWN           0.5451f,  0.2706f,  0.0745f,  1.0000f
#define FR_INDIANRED             0.8039f,  0.3608f,  0.3608f,  1.0000f
#define FR_SNOW                  1.0000f,  0.9804f,  0.9804f,  1.0000f
#define FR_STEELBLUE             0.2745f,  0.5098f,  0.7059f,  1.0000f
#define FR_MEDIUMSLATEBLUE       0.4824f,  0.4078f,  0.9333f,  1.0000f
#define FR_BLACK                 0.0000f,  0.0000f,  0.0000f,  1.0000f
#define FR_LIGHTBLUE             0.6784f,  0.8471f,  0.9020f,  1.0000f
#define FR_TURQUOISE             0.2510f,  0.8784f,  0.8157f,  1.0000f
#define FR_MEDIUMVIOLETRED       0.7804f,  0.0824f,  0.5216f,  1.0000f
#define FR_DARKVIOLET            0.5804f,  0.0000f,  0.8275f,  1.0000f
#define FR_DARKGRAY              0.6627f,  0.6627f,  0.6627f,  1.0000f
#define FR_SECIAL_GRAY           0.9101f,  0.9101f,  0.9101f,  1.0000f
#define FR_SALMON                0.9804f,  0.5020f,  0.4471f,  1.0000f
#define FR_DARKMAGENTA           0.5451f,  0.0000f,  0.5451f,  1.0000f
#define FR_TOMATO                1.0000f,  0.3882f,  0.2784f,  1.0000f
#define FR_WHITESMOKE            0.9608f,  0.9608f,  0.9608f,  1.0000f
#define FR_GOLDENROD             0.8549f,  0.6471f,  0.1255f,  1.0000f
#define FR_MEDIUMSPRINGGREEN     0.0000f,  0.9804f,  0.6039f,  1.0000f
#define FR_DODGERBLUE            0.1176f,  0.5647f,  1.0000f,  1.0000f
#define FR_AQUA                  0.0000f,  1.0000f,  1.0000f,  1.0000f
#define FR_FORESTGREEN           0.1333f,  0.5451f,  0.1333f,  1.0000f
#define FR_LEMONCHIFFON          1.0000f,  0.9804f,  0.8039f,  1.0000f
#define FR_LIGHTSLATEGRAY        0.4667f,  0.5333f,  0.6000f,  1.0000f
#define FR_SLATEGRAY             0.4392f,  0.5020f,  0.5647f,  1.0000f
#define FR_LIGHTGRAY             0.8275f,  0.8275f,  0.8275f,  1.0000f
#define FR_INDIGO                0.2941f,  0.0000f,  0.5098f,  1.0000f
#define FR_CADETBLUE             0.3725f,  0.6196f,  0.6275f,  1.0000f
#define FR_LIGHTYELLOW           1.0000f,  1.0000f,  0.8784f,  1.0000f
#define FR_DARKORANGE            1.0000f,  0.5490f,  0.0000f,  1.0000f
#define FR_POWDERBLUE            0.6902f,  0.8784f,  0.9020f,  1.0000f
#define FR_ROYALBLUE             0.2549f,  0.4118f,  0.8824f,  1.0000f
#define FR_SIENNA                0.6275f,  0.3216f,  0.1765f,  1.0000f
#define FR_THISTLE               0.8471f,  0.7490f,  0.8471f,  1.0000f
#define FR_LIME                  0.0000f,  1.0000f,  0.0000f,  1.0000f
#define FR_SEASHELL              1.0000f,  0.9608f,  0.9333f,  1.0000f
#define FR_DARKRED               0.5451f,  0.0000f,  0.0000f,  1.0000f
#define FR_LIGHTSKYBLUE          0.5294f,  0.8078f,  0.9804f,  1.0000f
#define FR_SPECIAL_BLUE          0.7421f,  0.8828f,  0.9218f,  1.0000f            //Default grid color
#define FR_YELLOWGREEN           0.6039f,  0.8039f,  0.1961f,  1.0000f
#define FR_AQUAMARINE            0.4980f,  1.0000f,  0.8314f,  1.0000f
#define FR_LIGHTCORAL            0.9412f,  0.5020f,  0.5020f,  1.0000f
#define FR_DARKSLATEGRAY         0.1843f,  0.3098f,  0.3098f,  1.0000f
#define FR_KHAKI                 0.9412f,  0.9020f,  0.5490f,  1.0000f
#define FR_DARKGREY              0.6627f,  0.6627f,  0.6627f,  1.0000f
#define FR_BURLYWOOD             0.8706f,  0.7216f,  0.5294f,  1.0000f
#define FR_LIGHTGOLDENRODYELLOW  0.9804f,  0.9804f,  0.8235f,  1.0000f
#define FR_MEDIUMBLUE            0.0000f,  0.0000f,  0.8039f,  1.0000f
#define FR_DARKSALMON            0.9137f,  0.5882f,  0.4784f,  1.0000f
#define FR_ROSYBROWN             0.7373f,  0.5608f,  0.5608f,  1.0000f
#define FR_LIGHTSALMON           1.0000f,  0.6275f,  0.4784f,  1.0000f
#define FR_PALEVIOLETRED         0.8588f,  0.4392f,  0.5765f,  1.0000f
#define FR_CORAL                 1.0000f,  0.4980f,  0.3137f,  1.0000f
#define FR_VIOLET                0.9333f,  0.5098f,  0.9333f,  1.0000f
#define FR_GREY                  0.5020f,  0.5020f,  0.5020f,  1.0000f
#define FR_LIGHTGREEN            0.5647f,  0.9333f,  0.5647f,  1.0000f
#define FR_LINEN                 0.9804f,  0.9412f,  0.9020f,  1.0000f
#define FR_ORANGERED             1.0000f,  0.2706f,  0.0000f,  1.0000f
#define FR_DIMGRAY               0.4118f,  0.4118f,  0.4118f,  1.0000f
#define FR_MAROON                0.5020f,  0.0000f,  0.0000f,  1.0000f
#define FR_LIGHTPINK             1.0000f,  0.7137f,  0.7569f,  1.0000f
#define FR_MEDIUMAQUAMARINE      0.4000f,  0.8039f,  0.6667f,  1.0000f
#define FR_OLDLACE               0.9922f,  0.9608f,  0.9020f,  1.0000f
#define FR_GLASS                 0.3300f,  1.0000f,  1.0000f,  1.0000f
};

#include<fr_callbacks.h>
class Fr_GL3Window; // compiler should define that later. 

class FR {
	FR() {}; //NO need for a constructor.
public:
	//static variables used for mouse events inside fgwl.
	static int glfw_e_x;  //SAVE X AND Y OF LAST CLICK INSIDE GLFW
	static int glfw_e_y;
	static int glfw_click;
	static int glfw_double_click;
	static int glfw_MouseClicked;
	static int glfw_MouseButton;
	
	//Avoid running GLFW OR GLAD CODE whiel GLFW is not created
	static bool s_GLFWInitialized;
	static bool s_GladInitialized;

	static Fr_GL3Window* globalP_pWindow;

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
