//                                                                      
// This file is a part of the Open Source Design456App                    
// IT License
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