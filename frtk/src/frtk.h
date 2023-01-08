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

#ifndef FRTK_H
#define FRTK_H

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <stdarg.h>
#include <unordered_map>
#include <unordered_set>


#include <FL/Fl.H>
#include <FL/fl_types.h>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Window.H>


#include<glad/glad.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <Fr_GL3Window.h>
#include <FL/platform.H>

#include <FL/gl.h> // for gl_texture_reset()
#include <Fr_Log.h>
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include <FR.h>




//drawing
#include<fr_widgets/fr_basic_shapes.h>


#endif