/*                                                                      *
 This file is a part of the Open Source Design456App                    *
                                                                *
 Copyright (C) 2023                                                     *
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
 <http://www.gnu.org/licenses/>										*
 .																*
 Author :Mariwan Jalal    mariwan.jalal@gmail.com                        *
*/

#include "Fr_Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Fr_Log::s_FRTKLogger;
std::shared_ptr<spdlog::logger> Fr_Log::s_APPLogger;

void Fr_Log::Init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");
    s_FRTKLogger = spdlog::stdout_color_mt("FRTK");
    s_FRTKLogger->set_level(spdlog::level::trace);

    s_APPLogger = spdlog::stdout_color_mt("APP");
    s_APPLogger->set_level(spdlog::level::trace);
}