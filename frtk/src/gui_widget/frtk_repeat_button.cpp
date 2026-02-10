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

#include <gui_widget/frtk_repeat_button.h>

namespace FR {
    Frtk_Repeat_Button::Frtk_Repeat_Button(NVGcontext* vg, float x, float y, float w, float h, std::string l, BOX_TYPE b) :
        Frtk_Button(vg, x, y, w, h, l, b),
        m_delayBeforeStart(0.5f), m_delayBetweenCallbacks(0.1f), m_repeatTimer(0.0f)
    {
        m_wdgType = FRTK_REPEAT_BUTTON;
        m_lastTime = std::chrono::high_resolution_clock::now();
    }
    void Frtk_Repeat_Button::delayBetweenCallbacks(float val)
    {
        m_delayBetweenCallbacks = val;
    }
    void Frtk_Repeat_Button::startDelay(float val)
    {
        m_delayBeforeStart = val;
    }
    float Frtk_Repeat_Button::delayBetweenCallbacks()
    {
        return m_delayBetweenCallbacks;
    }
    float Frtk_Repeat_Button::startDelay()
    {
        return m_delayBeforeStart;
    }

    int Frtk_Repeat_Button::handle(int e) {
        auto now = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta = now - m_lastTime;
        m_lastTime = now;
        float delta_time = delta.count();

            if (e == FR_LEFT_PUSH) {
                m_repeatTimer = m_delayBeforeStart;
                m_value = 1;
                m_Image.opacity = 0.5;

                return 1;
            }
            else if (e == FR_LEFT_RELEASE) {
                m_repeatTimer = 0.0f; // stop repeating
                m_value = 0;
                m_Image.opacity = 1.0;

                return 1;
            }

        // Update repeat timer if button is held
        if (m_repeatTimer > 0.0f) {
            m_repeatTimer -= delta_time;
            if (m_repeatTimer <= 0.0f) {
                do_callback();
                m_repeatTimer = m_delayBetweenCallbacks; 
            }
        }
        return 0;
    }
}