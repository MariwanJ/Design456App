//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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

#include <fr_application.h>
int main(int argc, char** argv)
{
    //for (int i = 0; i < 100; ++i) {
    //    printf("i=%u",i);
    //    printf("genid =%8X\n", FR::genID());
    //    }
    std::string path;
        //FR_PROFILE_BEGIN_SESSION("Startup", "Design456Profile-Startup.json");
    //std::shared_ptr<FR::Fr_Application> Design456App =std::make_shared<FR::Fr_Application>(); // Cause OpenGL to now work properly
    FR::Fr_Application *Design456App = new FR::Fr_Application();
    
    FR::Fr_Log::Init();
    FR::Fr_Log::GetAPPLogger()->info("App Started!");
    // FR_PROFILE_END_SESSION();
    // FR_PROFILE_BEGIN_SESSION("Runtime", "Design456Profile-Runtime.json");
    return Design456App->run(argc, argv);
    // FR_PROFILE_END_SESSION();
}