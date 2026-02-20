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
        if (!Fr_Window::spWindow)
            return 0;

        Fr_Window* win = Fr_Window::spWindow.get();
        auto& ek = win->m_sysEvents.keyB;

        // Ctrl/Alt cancel navigation (used for shortcuts)
        if (ek.ctrlDown || ek.altDown)
            return 0;

        // Tab navigation (Shift reverses direction)
        if (ek.keyDown[GLFW_KEY_TAB]) {
            return ek.shiftDown ? GLFW_KEY_LEFT : GLFW_KEY_RIGHT;
        }

        // Arrow navigation
        if (ek.keyDown[GLFW_KEY_RIGHT]) return GLFW_KEY_RIGHT;
        if (ek.keyDown[GLFW_KEY_LEFT])  return GLFW_KEY_LEFT;
        if (ek.keyDown[GLFW_KEY_UP])    return GLFW_KEY_UP;
        if (ek.keyDown[GLFW_KEY_DOWN])  return GLFW_KEY_DOWN;

        return 0;
    }


    Frtk_GrpWidget::Frtk_GrpWidget(NVGcontext* vg, float X, float Y, float W, float H, std::string label, BOX_TYPE b) :
        Frtk_Widget(X, Y, W, H, label, b), m_childFocus(NULL), m_grabbedChild(NULL) {
        m_vg = vg;
        m_wdgType = FRTK_GROUP;
        m_font.pos.x = m_x;
        m_font.pos.y = m_y;
        m_font.size.w = m_w;
        m_font.size.h = m_h;
    }
    Frtk_GrpWidget::~Frtk_GrpWidget() {
    }

    void Frtk_GrpWidget::draw() {
        if (m_visible) {
            drawBox();
            draw_focus();
            drawLabel();
            draw_children();
        }
    }
    void Frtk_GrpWidget::draw_children() {
        nvgSave(m_vg);                // save current transform and state
        nvgTranslate(m_vg, x(), m_y);  // shift drawing origin to parent
        for (auto wdg : m_children) {
            if (wdg->visible()) {
                wdg->draw();
            }
        }
        nvgRestore(m_vg);             // restore previous transform
    }

    void Frtk_GrpWidget::redraw() {
        if (m_visible) {
            draw();
        }
    }

    void Frtk_GrpWidget::drawBox() {
        if (m_visible) {
            draw_box(m_vg, m_boxType, { {m_x, m_y}, {m_w, m_h} }, 0.0, NORMAL_BORDER,
                glmToNVG(m_color),
                glmToNVG(m_borderColor), true);
        }
    }

    void Frtk_GrpWidget::drawBox(BOX_TYPE t, glm::vec4 c) {
        if (m_visible) {
            m_color = c;
            m_boxType = t;
            drawBox();
        }
    }
    void Frtk_GrpWidget::drawBox(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 c) {
        if (m_visible) {
            m_x = X;
            m_y = Y;
            m_w = W;
            m_h = H;
            m_boxType = t;
            m_color = c;
            drawBox();
        }
    }

    int Frtk_GrpWidget::send_event(Frtk_Widget& w, int ev) {
        return w.handle(ev);
    }
    int Frtk_GrpWidget::findIndex(const std::shared_ptr<Frtk_Widget>& w) const {
        auto it = std::find(m_children.begin(), m_children.end(), w);
        if (it != m_children.end())
            return std::distance(m_children.begin(), it);
        return -1;
    }

    int Frtk_GrpWidget::getChildrenNo() {
        return m_children.size();
    }

    std::shared_ptr<Frtk_Widget> Frtk_GrpWidget::getChildAt(size_t index) {
        if (index >= 0 && index < m_children.size()) {
            return m_children.at(index);
        }
        else return nullptr;
    }

    int Frtk_GrpWidget::remove_child_at(size_t index) {
        if (index > m_children.size()) 
            return -1;
        m_children.erase(m_children.begin() + index);
        return 0;
    }
    const std::vector<std::shared_ptr<Frtk_Widget>>& Frtk_GrpWidget::getChildren() const {
        return m_children;
    }

    int Frtk_GrpWidget::remove_child(std::shared_ptr<Frtk_Widget>& wdg) {
        auto it = std::find(m_children.begin(), m_children.end(), wdg);
        if (it != m_children.end()) {
            m_children.erase(it);
            return 0;
        }
        return -1;
    }

    void Frtk_GrpWidget::remove_all() {
        m_children.clear();
    }
    void Frtk_GrpWidget::addChild(std::shared_ptr<Frtk_Widget> w)
    {
        w->parent(this);
        m_children.emplace_back(std::move(w));
    }

    bool Frtk_GrpWidget::restore_focus() {
        // Try saved
        // first
        if (m_childFocus) {
            if (m_childFocus->take_focus()) {
                return true;
            }
        }

        // try the first can focus child
        for (auto& wdg : m_children) {
            if (wdg->take_focus()) return true;
        }
        return false;
    }
    bool Frtk_GrpWidget::navigate_focus(int key) {
        if (m_children.empty()) return false; // nothing to navigate
        int currentIndex = -1;
        for (size_t i = 0; i < m_children.size(); i++) {
            if (m_children[i].get() == m_childFocus) {
                currentIndex = static_cast<int>(i);
                break;
            }
        }

        int startIndex = currentIndex;

        while (true) {
            // Move index based on key
            switch (key) {
            case GLFW_KEY_RIGHT:
            case GLFW_KEY_DOWN:
                currentIndex++;
                if (currentIndex >= static_cast<int>(m_children.size()))
                    currentIndex = 0; // wrap
                break;

            case GLFW_KEY_LEFT:
            case GLFW_KEY_UP:
                currentIndex--;
                if (currentIndex < 0)
                    currentIndex = static_cast<int>(m_children.size()) - 1; // wrap
                break;

            default:
                return false; // unknown key
            }

            // Came back to start -> stop
            if (currentIndex == startIndex) return false;

            Frtk_Widget* candidate = m_children[currentIndex].get();

            // If candidate is a group, recursively navigate inside it
            if (candidate->m_wdgType== FRTK_GROUP) {
                Frtk_GrpWidget* group = static_cast<Frtk_GrpWidget*>(candidate);
                Frtk_Widget* nested = group->first_focusable_widget();
                if (nested && nested->take_focus()) {
                    m_childFocus = nested;
                    return true;
                }
            }
            else {
                // Leaf widget -> try to take focus
                if (candidate->take_focus()) {
                    m_childFocus = candidate;
                    return true;
                }
            }
        }

        return false;
    }
    Frtk_Widget* Frtk_GrpWidget::first_focusable_widget() {
        for (auto& child : m_children) {
            Frtk_Widget* w = child.get();

            if (w->can_focus()) return w;

            if (w->m_wdgType == FRTK_GROUP) {
                Frtk_GrpWidget* group = static_cast<Frtk_GrpWidget*>(w);
                Frtk_Widget* nested = group->first_focusable_widget();
                if (nested) return nested;
            }
        }
        return nullptr;
    }

    void Frtk_GrpWidget::lose_focus() {
        // Called when widget loses focus
        // Group keeps m_savedFocus pointing to last focused child
        if (m_parent)
            m_parent->set_child_focus(g_focusedWdgt.prev);
        g_focusedWdgt.prev = g_focusedWdgt.current;
        g_focusedWdgt.current = nullptr;
        m_has_focus = false;
        for (auto& wdg : m_children) {
            wdg->lose_focus();
        }
    }

    Frtk_Widget* Frtk_GrpWidget::focusedChild()
    {
        return m_childFocus;
    }

    bool Frtk_GrpWidget::set_child_focus(Frtk_Widget* w) {
        m_childFocus = w;
        return true;
    }

    dimPos_float_t Frtk_GrpWidget::mainGui() const {
        return { m_x, m_y + FRTK_WINDOWS_TITLE_HEIGHT };
    }

    //Return = 1 Event consumed
    //Return = 0 or -1 Event should continue to be delivered to other widgets
    //Return = 1 Event consumed
    //Return = 0 or -1 Event should continue to be delivered to other widgets
    int Frtk_GrpWidget::handle(int ev) {
        //Keyboard events
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
                }break;
            }
            }
            return 0;
        }
        case FR_UNFOCUS: {
            m_childFocus = g_focusedWdgt.prev;
            return 0;
        }
        case FR_KEYBOARD: {
            if (m_childFocus && m_childFocus->active() && m_childFocus->visible()) {
                if (m_childFocus->handle(FR_KEYBOARD) == 1)
                    return 1;   // child consumed key
            }
            if (navigate_focus(navkey()))
                return 1;
            return 0;
            }
        }

        //Mouse 
           if (!(m_active && m_visible))
                return 0;              //inactive widget - we don't care
            switch (ev) {
            case FR_ENTER:
            case FR_MOUSE_MOVE:
            {
                if (m_grabbedChild) {
                    return m_grabbedChild->handle(ev);
                }
                Frtk_Widget* hovered = nullptr;
                for (auto& wdg : m_children) {
                    if (!wdg->visible() || !wdg->active())
                        continue;

                    if (wdg->isMouse_inside()) {
                        hovered = wdg.get();
                        break;      // top-most hit wins
                    }
                }

                for (auto& wdg : m_children) {
                    if (!wdg->visible())
                        continue;

                    if (wdg.get() == hovered) {
                        if (!wdg->hasBelowMouse()) {
                            wdg->set_BelowMouse();
                            if (wdg->handle(FR_ENTER) == 1)
                                return 1;
                        }
                    }
                    else {
                        if (wdg->hasBelowMouse()) {
                            wdg->clear_BelowMouse();
                            if (wdg->handle(FR_LEAVE) == 1) {
                                return 1;
                            }
                        }
                    }
                }
             
            }break;
            }
            for (auto& wdg : m_children) {
                //We should not allow sending events to inactive widget
                if (wdg->active() && wdg->visible()) {
                    if (wdg->isMouse_inside()) {
                        int result = wdg->handle(ev);
                        if (ev == FR_LEFT_PUSH) {
                            result |= wdg->take_focus();
                        }
                        if (result == 1) {
                            return result; // Event is consumed
                        }
                    }
                }
            }
            return 0;
        }  
        bool Frtk_GrpWidget::take_focus() {
            m_has_focus = true;
            Frtk_Widget* first = first_focusable_widget();
            if (!first) return false;

            return first->take_focus();
        }
    

}