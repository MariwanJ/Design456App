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
#ifndef FR_LOG_H
#define FR_LOG_H


#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"


class  Fr_Log
{
public:
    static void Init();
    inline static std::shared_ptr<spdlog::logger>& GetFRTKLogger() { return s_FRTKLogger; }
    inline static std::shared_ptr<spdlog::logger>& GetAPPLogger() { return s_APPLogger; }

private:
    static std::shared_ptr<spdlog::logger> s_FRTKLogger;
    static std::shared_ptr<spdlog::logger> s_APPLogger;
};

// log macros
#define FRTK_CORE_TRACE(...)    Fr_Log::GetFRTKLogger()->trace(__VA_ARGS__)
#define FRTK_CORE_INFO(...)     Fr_Log::GetFRTKLogger()->info(__VA_ARGS__)
#define FRTK_CORE_WARN(...)     Fr_Log::GetFRTKLogger()->warn(__VA_ARGS__)
#define FRTK_CORE_ERROR(...)    Fr_Log::GetFRTKLogger()->error(__VA_ARGS__)
#define FRTK_CORE_FATAL(...)    Fr_Log::GetFRTKLogger()->fatal(__VA_ARGS__)

// Application
#define APP_APP_TRACE(...)	   Fr_Log::GetAPPLogger()->trace(__VA_ARGS__)
#define APP_APP_INFO(...)	   Fr_Log::GetAPPLogger()->info(__VA_ARGS__)
#define APP_APP_WARN(...)	   Fr_Log::GetAPPLogger()->warn(__VA_ARGS__)
#define APP_APP_ERROR(...)	   Fr_Log::GetAPPLogger()->error(__VA_ARGS__)
#define APP_APP_FATAL(...)	   Fr_Log::GetAPPLogger()->fatal(__VA_ARGS__)

#endif