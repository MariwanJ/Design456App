/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                        *
 Copyright (C) 2023                                                     *
                                                                        *
                                                                        *
 This library is free software; you can redistribute it and/or          *
 modify it under the terms of the GNU Lesser General Public             *
 License as published by the Free Software Foundation; either           *
 version 2 of the License, or (at your option) any later version.       *
                                                                        *
 This library is distributed in the hope that it will be useful,        *
 but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 Lesser General Public License for more details.                        *
                                                                        *
 You should have received a copy of the GNU Lesser General Public       *
 License along with this library; if not, If not, see                   *
 <http://www.gnu.org/licenses/>                                         *
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                       *
*/
#include <FL/Fl_Button.H>
#include <Fr_GL3Window.h>
/* Main application code */
int main(int argc, char** argv)
{
    Fr_GL3Window* win = new Fr_GL3Window(0, 0, 900, 600, "test");
    win->begin();
    win->label("Click GL panel to reshape");
    win->resizable(win);
    Fl_Button* b = new Fl_Button(10, 5, 50, 40, "clickme");
    win->end();
    win->show();
    Fl::run();
}