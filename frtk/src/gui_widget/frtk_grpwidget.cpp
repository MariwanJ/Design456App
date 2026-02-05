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

#include <gui_widget/frtk_grpwidget.h>

namespace FR {
    // translate the current keystroke into up/down/left/right for navigation:
    static int navkey() {
        if (Fr_Window::spWindow == nullptr)
            return 0; //do nothing
        auto& ek = Fr_Window::spWindow->m_sysEvents.keyB;
        // The app may want these for hotkeys, check key state
        if (ek.ctrlDown || ek.shiftDown || ek.altDown) return 0;
        else if (ek.keyDown[GLFW_KEY_TAB]) {
            if (ek.shiftDown) return GLFW_KEY_RIGHT;
            else return GLFW_KEY_LEFT;
        }
        else if (ek.keyDown[GLFW_KEY_RIGHT])      return GLFW_KEY_RIGHT;
        else if (ek.keyDown[GLFW_KEY_LEFT])       return GLFW_KEY_LEFT;
        else if (ek.keyDown[GLFW_KEY_UP])         return GLFW_KEY_UP;
        else if (ek.keyDown[GLFW_KEY_DOWN])       return GLFW_KEY_DOWN;
        else                                     return 0;
    }

    Frtk_GrpWidget::Frtk_GrpWidget(NVGcontext* vg, float X, float Y, float W, float H, std::string label, BOX_TYPE b) :Frtk_Widget(X, Y, W, H, label, b) {
        m_wdgType = FRTK_GROUP;
    }
    Frtk_GrpWidget::~Frtk_GrpWidget() {
    }

    void Frtk_GrpWidget::draw() {
        if (visible()) {
            drawBox();
            draw_focus();
            drawLabel();
        }
    }
    void Frtk_GrpWidget::draw_children() {
        for (auto wdg : m_children) {
            if (wdg->visible()) {
                wdg->draw();
            }
        }
    }

    void Frtk_GrpWidget::redraw_children()
    {
        for (auto wdg : m_children) {
            if (wdg->visible()) {
                wdg->redraw();
            }
        }
    }

    void Frtk_GrpWidget::redraw() {
        if (visible()) {
            draw();
            drawLabel();
        }
    }

    void Frtk_GrpWidget::drawBox() {
        if (visible()) {
            drawBox(BOX_TYPE::FRTK_UP_FRAME, m_x, m_y, m_w, m_h, m_color);
            for (auto wdg : m_children) {
                drawBox(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
            }
        }
    }

    void Frtk_GrpWidget::drawBox(BOX_TYPE t, glm::vec4 c) {
        if (visible()) {
            color(c);
            drawBox(t, m_x, m_y, m_w, m_h, c);

            for (auto wdg : m_children) {
                drawBox(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
            }
        }
    }
    void Frtk_GrpWidget::drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) {
        if (visible()) {
            //we should draw the box here :
            for (auto wdg : m_children) {
                drawBox(wdg->boxtype(), wdg->x(), wdg->y(), wdg->w(), wdg->h(), wdg->color());
            }
        }
    }
    void Frtk_GrpWidget::draw_focus() {
    }
    void Frtk_GrpWidget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H) {
    }
    void Frtk_GrpWidget::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) {
    }

    int Frtk_GrpWidget::send_event(Frtk_Widget& w, int ev) {
        if (w.should_getEvent(false)) {
            return w.handle(ev);
        }
    }
    int Frtk_GrpWidget::findIndex(const std::shared_ptr<Frtk_Widget>& w) const {
        auto it = std::find(m_children.begin(), m_children.end(), w);
        if (it != m_children.end())
            return std::distance(m_children.begin(), it);
        return -1;
    }

    void Frtk_GrpWidget::remove_children(size_t index) {
        m_children.erase(m_children.begin() + index);
    }
    void Frtk_GrpWidget::remove_all() {
        m_children.clear();
    }
    void Frtk_GrpWidget::addChild(std::shared_ptr<Frtk_Widget> w)
    {
        w->parent(this);
        m_children.push_back(std::move(w));
    }

    bool Frtk_GrpWidget::restore_focus() {
        // Try saved focus first
        if (m_childFocus) {
            if (m_childFocus->take_focus()) {
                return true;
            }
        }

        // try the first focusable child
        for (auto& wdg : m_children) {
            if (wdg->take_focus()) return true;
        }
        return false;
    }
    bool Frtk_GrpWidget::navigate_focus(int key) {
        if (m_children.size() <= 1) return false;  // nothing to navigate

        int currentIndex = -1;
        for (size_t i = 0; i < m_children.size(); i++) {
            if (m_children[i].get() == m_childFocus) {
                currentIndex = static_cast<int>(i);
                break;
            }
        }

        int startIndex = currentIndex;

        while (true) {
            // move index
            switch (key) {
            case GLFW_KEY_RIGHT:
            case GLFW_KEY_DOWN:
                currentIndex++;
                if (currentIndex >= static_cast<int>(m_children.size())) currentIndex = 0; // wrap
                break;

            case GLFW_KEY_LEFT:
            case GLFW_KEY_UP:
                currentIndex--;
                if (currentIndex < 0) currentIndex = static_cast<int>(m_children.size()) - 1; // wrap
                break;

            default:
                return false;  // unknown key
            }

            if (currentIndex == startIndex) return false;

            Frtk_Widget* candidate = m_children[currentIndex].get();

            if (key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) {
                if (m_childFocus) {
                    int prevX = m_childFocus->x();
                    int prevW = m_childFocus->w();
                    int candX = candidate->x();
                    int candW = candidate->w();
                    if (candX >= prevX + prevW || candX + candW <= prevX) continue;
                }
            }

            if (candidate->take_focus()) return true;
        }
        return false;
    }

    void Frtk_Widget::lose_focus() {
        // Called when widget loses focus
        // Group keeps m_savedFocus pointing to last focused child
        if (m_parent) m_parent->set_child_focus(g_focusedWdgt.prev);
        g_focusedWdgt.prev = g_focusedWdgt.current;
        g_focusedWdgt.current = nullptr;
    }

    //Return = 1 Event consumed
   //Return = 0 or -1 Event should continue to be delivered to other widgets
    int Frtk_GrpWidget::handle(int ev) {
        switch (ev) {
        case FR_FOCUS: {
            switch (navkey()) {
            default: {
                if (m_childFocus != nullptr && m_childFocus->take_focus()) {
                    return 1;
                }
                return 0;
            }

            case GLFW_KEY_RIGHT:
            case GLFW_KEY_DOWN: {
                for (auto& wdg : m_children) {
                    if (wdg->take_focus()) return 1;
                }
                break;
            }

            case GLFW_KEY_LEFT:
            case GLFW_KEY_UP: {
                for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
                    if ((*it)->take_focus()) return 1;
                }
                break;
            }
            }
            return 0;
        }

        case FR_UNFOCUS: {
            m_childFocus = g_focusedWdgt.prev;
            return 0;
        } break;
        case FR_KEYBOARD: {
            return (navigate_focus(navkey()));
        }break;

        case FR_ENTER:
        case FR_MOUSE_MOVE:
        {
            // Iterate children in reverse order (topmost child first)
            for (auto it = m_children.rbegin(); it != m_children.rend(); ++it) {
                Frtk_Widget* child = it->get();

                if (!child->visible()) continue;

                // Check if mouse is inside this child
                if (child->should_getEvent(false)) {
                    if (child->hasBelowMouse()) {
                        return send_event(*child, FR_MOUSE_MOVE);
                    }
                    else {
                        // Mouse just entered this child
                        set_BeloMouse();
                        if (send_event(*child, FR_ENTER)) return 1;
                    }
                }
            }
            // No child handled it // mark this group as under the mouse
            set_BeloMouse();
            return 1;
        }break;
        return 0;
        }

        if (should_getEvent(false)) {
            for (auto& wdg : m_children) {
                int result = wdg->handle(ev);
                if (result == 1) {
                    return 1; // Event is consumed
                }
            }
        }
        return 0;
    }

    bool Frtk_GrpWidget::set_child_focus(Frtk_Widget* w) {
        m_childFocus = w;
        return true;
    }
}