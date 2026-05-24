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

#include <gui_widget/frtk_tree_item.h>
#include <gui_widget/frtk_tree.h>
#include <gui_widget/frtk_draw.h>

namespace FR {
    Frtk_Tree_Item::Frtk_Tree_Item(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) :
        Frtk_GrpWidget(vg, X, Y, W, H, lbl, b), m_itemType(FRTK_TREE_ITEM_NONE), m_level(-1),
        m_cachedWidth(0.0f), m_dirty(true), m_selected(false), m_open(false), m_draggin(false)
    {
        m_wdgType = FRTK_TREE_ITEM_WIDGET;
        m_style.Hpadding = 2.0f;
        m_style.Vpadding = 2.0f;
        m_style.itemHeight = 16.0f;
        m_style.halfVline = m_style.itemHeight * 0.5f;
        m_style.hArm = 8.0f;
        m_style.toggleIcon = { {0, 0.f} ,{ 9.0f,9.0f } };
        m_style.lineWidth = 1.5f;
        m_style.lineColor = nvgRGBAf(FR_BLACK);
        m_style.bgColor = nvgRGBAf(FR_LIGHT_GRAY);
        m_style.selColor = nvgRGBAf(FR_LIGHTYELLOW);
        m_font.lblAlign = NVG_ALIGN_MIDDLE_LEFT | NVG_ALIGN_INSIDE;
        m_itemType = FRTK_TREE_ITEM_MIDDLE;
    }
    Frtk_Tree_Item::~Frtk_Tree_Item()
    {
    }
    int Frtk_Tree_Item::getWidth()
    {
        if (m_dirty) {
            m_cachedWidth = getTextWidth(m_vg, m_label, m_font.fontSize, m_font.fName.c_str()) + m_style.toggleIcon.size.w + m_style.Hpadding;
            m_dirty = false;
        }
        return m_cachedWidth;
    }

    int Frtk_Tree_Item::getSubtreeWidth()
    {
        int width = getWidth();

        if (hasChildren() && m_open) {
            for (auto child : m_children) {
                std::shared_ptr<Frtk_Tree_Item> item = std::dynamic_pointer_cast<Frtk_Tree_Item> (child);
                width = std::max(width, item->getSubtreeWidth());
            }
        }
        return width;
    }
    bool Frtk_Tree_Item::isOpen(void)
    {
        return m_open;
    }
    bool Frtk_Tree_Item::isTail()
    {
        return (m_itemType == FRTK_TREE_ITEM_TAIL);
    }

    bool Frtk_Tree_Item::hasChildren() {
        return (m_children.size() > 0);
    }

    void Frtk_Tree_Item::drawNode()
    {
        Frtk_Tree_Item* root = getRoot();
        iconImageSize_t* activeIcn;
        if (!root) {
            FRTK_CORE_WARN("Could not retrieve Root widget for the tree widget");
            return;
        }
        drawBackground();
        float X = m_x;
        float Y = m_y;
        float W = m_style.toggleIcon.size.w;
        float H = m_style.toggleIcon.size.h;
        m_style.toggleIcon.pos.x = m_x;
        m_style.toggleIcon.pos.y = m_y;
        if (!m_children.empty()) {
            drawIconBox();
        }
        //draw the L line
        if (root != this) {
            float x_line = parent()->x()+ m_style.hArm * (m_level-1);
            float y_line = parent()->y() + H* 0.5f;
            // | line
            nvgBeginPath(m_vg);
            nvgStrokeColor(m_vg, m_style.lineColor);
            nvgStrokeWidth(m_vg, m_style.lineWidth);
            nvgMoveTo(m_vg, m_style.Hpadding + 2 , H );
            nvgLineTo(m_vg, m_style.Hpadding + 2 , m_y + H *0.5);
            nvgStroke(m_vg);
            // ---- line
            nvgBeginPath(m_vg);
            nvgStrokeColor(m_vg, m_style.lineColor);
            nvgStrokeWidth(m_vg, m_style.lineWidth);
            nvgMoveTo(m_vg, m_style.Hpadding+2, m_y + H * 0.5f);
            if (m_children.empty())
                nvgLineTo(m_vg, m_x + W * 0.5f, m_y + H * 0.5f);
            else
                nvgLineTo(m_vg, m_style.Hpadding + m_style.hArm * (m_level+1) - W, m_y + H * 0.5f);
            nvgStroke(m_vg);
        }

        // icon image drawing and label
        Frtk_Tree* tree = static_cast<Frtk_Tree*> (root->parent());
        if (tree->defaultIcons.empty())
            return;
        if (!hasChildren()) {
            activeIcn = &tree->defaultIcons[2];
        }
        else if (isOpen()) {
            activeIcn = &tree->defaultIcons[1];
        }
        else
        {
            activeIcn = &tree->defaultIcons[0];
        }
        if (m_children.empty())
            activeIcn->dim.pos = { m_x + W* 0.5f , m_y - H *0.5f};
        else
            activeIcn->dim.pos = { m_x + m_style.toggleIcon.size.w + m_style.Hpadding, m_y - H * 0.5f };
        m_font.pos.x = activeIcn->dim.pos.x + activeIcn->dim.size.w + m_style.Hpadding;
        m_font.pos.y = Y+m_style.Vpadding + 2;
        drawLabel();
        drawImage();
    }

    void Frtk_Tree_Item::drawIconBox()
    {
        float cx = m_style.toggleIcon.pos.x;
        float cy = m_style.toggleIcon.pos.y;
        float W = m_style.toggleIcon.size.w;
        float H = m_style.toggleIcon.size.h;
        float arm = m_style.hArm;
        // outer square
        nvgBeginPath(m_vg);
        nvgStrokeColor(m_vg, m_style.lineColor);
        nvgStrokeWidth(m_vg, m_style.lineWidth);
        nvgRect(m_vg, cx , cy , W, H);
        nvgStroke(m_vg);
        if (!hasChildren())
            return;
        // horizontal arm (present for both + and -)
        nvgBeginPath(m_vg);
        nvgStrokeColor(m_vg, m_style.lineColor);
        nvgStrokeWidth(m_vg, m_style.lineWidth);
        nvgMoveTo(m_vg, cx + 2, cy + H * 0.5f);
        nvgLineTo(m_vg, cx + W -2, cy + H * 0.5f);
        nvgStroke(m_vg);
        if (!m_open) {
            // vertical : convert - symbol to +
            nvgBeginPath(m_vg);
            nvgStrokeColor(m_vg, m_style.lineColor);
            nvgStrokeWidth(m_vg, m_style.lineWidth);
            nvgMoveTo(m_vg, cx + W * 0.5f, cy + 2);
            nvgLineTo(m_vg, cx + W * 0.5f, cy + H - 2);
            nvgStroke(m_vg);
        }
    }

    // Selection highlight
    void Frtk_Tree_Item::drawBackground()
    {
        if (!m_selected)
            return;
        nvgBeginPath(m_vg);
        nvgRect(m_vg, m_x, m_y, m_w, m_style.itemHeight);
        nvgFillColor(m_vg, m_style.selColor);
        nvgFill(m_vg);
    }

    bool Frtk_Tree_Item::isRoot() const
    {
        return (m_parent->widgetType() == FRTK_TREE_WIDGET);
    }

    void Frtk_Tree_Item::updateChildren() {
        size_t count = m_children.size();
        if (count == 0) {
            m_itemType = FRTK_TREE_ITEM_TAIL;
            return;
        }
        for (size_t i = 0; i < count; ++i) {
            auto& child = m_children[i];
            if (!child)
                continue;
            std::shared_ptr< Frtk_Tree_Item> wdg = std::dynamic_pointer_cast<Frtk_Tree_Item>(child);
            if (i == 0 && wdg->m_parent == nullptr || wdg->m_parent->widgetType() == FRTK_TREE_WIDGET) {
                wdg->m_itemType = FRTK_TREE_ITEM_ROOT;
            }
            else if (i == count - 1) {
                wdg->m_itemType = FRTK_TREE_ITEM_TAIL;
            }
            else {
                wdg->m_itemType = FRTK_TREE_ITEM_MIDDLE;
            }
        }
    }

    int Frtk_Tree_Item::wdgImage(std::string path, std::optional<glm::vec4> tint)
    {
        FRTK_CORE_APP_ASSERT(false, "wdgImage is disable for Frtk_Tree_Item");
        return -1;
    }

    int Frtk_Tree_Item::wdgImage(const std::vector<uint8_t>& pngData, std::optional<glm::vec4> tint)
    {
        FRTK_CORE_APP_ASSERT(false, "wdgImage is disable for Frtk_Tree_Item");
        return -1;
    }

    void Frtk_Tree_Item::drawImage(Dim_float_t dim)
    {
        Frtk_Tree_Item* root = getRoot();
        iconImageSize_t* activeIcn;
        if (!root) {
            FRTK_CORE_WARN("Could not retrieve Root widget for the tree widget");
            return;
        }
        Frtk_Tree* tree = static_cast<Frtk_Tree*> (root->parent());

        if (tree->defaultIcons.empty())
            return;

        if (!hasChildren()) {
            activeIcn = &tree->defaultIcons[2];
            GLuint texture = tree->getIconTexture(TREE_ITEM_PAPER);
        }
        else if (isOpen()) {
            activeIcn = &tree->defaultIcons[1];
            GLuint texture = tree->getIconTexture(TREE_ITEM_OPEN);
        }
        else
        {
            activeIcn = &tree->defaultIcons[0];
            GLuint texture = tree->getIconTexture(TREE_ITEM_CLOSED);
        }
        activeIcn->dim = dim;
        drawImage();
    }

    Frtk_Tree_Item* Frtk_Tree_Item::getRoot() const {
        Frtk_Widget* parent = m_parent;
        Frtk_Widget* prevParent = const_cast<Frtk_Tree_Item*>(this);

        while (parent && parent->widgetType() != FRTK_TREE_WIDGET) {
            prevParent = parent;
            parent = parent->parent();
        }

        if (!parent || parent->widgetType() != FRTK_TREE_WIDGET)
            return nullptr;

        return static_cast<Frtk_Tree_Item*>(prevParent);
    }

    void Frtk_Tree_Item::drawImage()
    {
        Frtk_Tree_Item* root = getRoot();
        iconImageSize_t* activeIcn;
        if (root == nullptr)
        {
            FRTK_CORE_WARN("Root widget not found");
            return;
        }
        Frtk_Tree* tree = dynamic_cast<Frtk_Tree*>(root->parent());
        if (!tree) {
            FRTK_CORE_WARN("Root parent widget not found");
            return;
        }
        GLuint texture = 0;
        if (tree->defaultIcons.empty())
            return;

        if (!hasChildren()) {
            activeIcn = &tree->defaultIcons[2];
            texture = tree->getIconTexture(TREE_ITEM_PAPER);
        }
        else if (isOpen()) {
            activeIcn = &tree->defaultIcons[1];
            texture = tree->getIconTexture(TREE_ITEM_OPEN);
        }
        else
        {
            activeIcn = &tree->defaultIcons[0];
            texture = tree->getIconTexture(TREE_ITEM_CLOSED);
        }
        float x = floorf(activeIcn->dim.pos.x);
        float y = floorf(activeIcn->dim.pos.y);
        float w = floorf(activeIcn->dim.size.w);
        float h = floorf(activeIcn->dim.size.h);

        nvgGlobalAlpha(m_vg, activeIcn->opacity);
        nvgBeginPath(m_vg);
        nvgRect(m_vg, x, y, w, h);
        nvgFillPaint(m_vg, nvgImagePattern(m_vg, x, y, w, h, 0.0f, texture, 1.0f));
        nvgFill(m_vg);
    }

    void Frtk_Tree_Item::drawImage(float x, float y, float w, float h)
    {
        Frtk_Tree_Item* root = getRoot();
        iconImageSize_t* activeIcn;
        if (!root) {
            FRTK_CORE_WARN("Could not retrieve Root widget for the tree widget");
            return;
        }
        Frtk_Tree* tree = static_cast<Frtk_Tree*> (root->parent());
        if (tree->defaultIcons.empty())
            return;

        if (!hasChildren()) {
            activeIcn = &tree->defaultIcons[2];
            GLuint texture = tree->getIconTexture(TREE_ITEM_PAPER);
        }
        else if (isOpen()) {
            activeIcn = &tree->defaultIcons[1];
            GLuint texture = tree->getIconTexture(TREE_ITEM_OPEN);
        }
        else
        {
            activeIcn = &tree->defaultIcons[0];
            GLuint texture = tree->getIconTexture(TREE_ITEM_CLOSED);
        }
        activeIcn->dim = { {x,y}, {w,h} };
        drawImage();
    }

    void Frtk_Tree_Item::draw_focus() {
        if (!m_has_focus)
            return;

        Frtk_Tree_Item* root = getRoot();
        Frtk_Tree* tree = dynamic_cast<Frtk_Tree*>(root->parent());

        float X = m_font.pos.x - m_style.Hpadding - tree->defaultIcons[0].dim.size.w;
        float Y = 0.0f;

        if (isRoot())
            Y = - m_style.Vpadding;
        else
            Y = m_y - m_style.halfVline/2;

        float W = getWidth() + tree->defaultIcons[0].dim.size.w;
        float H = m_style.itemHeight;

        float step = 4.0f;   // spacing between dots
        float dot = 2.0f;   // length of each dot

        nvgSave(m_vg);
        nvgBeginPath(m_vg);
        // Top
        for (float i = 0; i < W; i += step) {
            nvgMoveTo(m_vg, X + i, Y);
            nvgLineTo(m_vg, X + i + dot, Y);
        }

        // Bottom
        for (float i = 0; i < W; i += step) {
            nvgMoveTo(m_vg, X + i, Y + H);
            nvgLineTo(m_vg, X + i + dot, Y + H);
        }

        // Left
        for (float i = 0; i < H; i += step) {
            nvgMoveTo(m_vg, X, Y + i);
            nvgLineTo(m_vg, X, Y + i + dot);
        }

        // Right
        for (float i = 0; i < H; i += step) {
            nvgMoveTo(m_vg, X + W, Y + i);
            nvgLineTo(m_vg, X + W, Y + i + dot);
        }
        nvgStroke(m_vg);

        // Fill
        nvgBeginPath(m_vg);
        nvgRect(m_vg, X, Y, W, H);
        nvgFillColor(m_vg, nvgRGBAf(0.2f, 0.5f, 1.0f, FRTK_FOCUS_OPACITY_VALUE));
        nvgFill(m_vg);
        nvgRestore(m_vg);
    }

    void Frtk_Tree_Item::draw_focus(BOX_TYPE t, float X, float Y, float W, float H) {
        if (!m_has_focus)
            return;
        draw_box(m_vg, t, { {X,Y},{W,H} }, m_cornerRadius, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
    }

    void Frtk_Tree_Item::draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) {
        if (!m_has_focus)
            return;
        draw_box(m_vg, t, { {X,Y},{W,H} }, m_cornerRadius, FRTK_NORMAL_BORDER, nvgRGBAf(0, 0.501f, 1.0f, 1.0f), nvgRGBAf(bkg.r, bkg.g, bkg.b, bkg.a), true);
    }

    void Frtk_Tree_Item::itemType(treeItemtype_t type)
    {
        m_itemType = type;
    }

    treeItemtype_t Frtk_Tree_Item::itemType()
    {
        return m_itemType;
    }

    void Frtk_Tree_Item::draw()
    {
        if (!m_visible)
            return;
        switch (m_itemType) {
        case FRTK_TREE_ITEM_NONE: {
            FRTK_CORE_APP_ASSERT(false, "You should not use this in production!!");
            return;
        } break;
        default:
            drawNode();
        }
        if (hasChildren() && isOpen())
            draw_children();
        draw_focus();
    }

    bool Frtk_Tree_Item::isPluseClicked() {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float localMouseX = mouse.activeX - absX()+m_x;
        float localMouseY = mouse.activeY - absY()+m_y;
        return (localMouseX >= m_style.toggleIcon.pos.x &&
                localMouseX <= m_style.toggleIcon.pos.x + m_style.toggleIcon.size.w &&
                localMouseY >= m_style.toggleIcon.pos.y &&
                localMouseY <= m_style.toggleIcon.pos.y + m_style.toggleIcon.size.h);
    }

    bool Frtk_Tree_Item::isItemClick() {
        auto mouse = m_mainWindow->m_sysEvents.mouse;
        float localMouseX = mouse.activeX - absX() + m_x;
        float localMouseY = mouse.activeY - absY() + m_y;
        return (localMouseX >= m_x && localMouseX <= m_x + getWidth() + m_style.Hpadding * 0.5f &&
            localMouseY> m_y && localMouseY < m_y + m_style.itemHeight);
    }

    void Frtk_Tree_Item::clearFocusAll()
    {
        focus(false);
        for (auto& child : m_children) {
            if (child)
                child->clearFocusAll();
        }
    }

    void Frtk_Tree_Item::addChild(std::shared_ptr<Frtk_Widget> wdg)
    {
        auto item = std::dynamic_pointer_cast<Frtk_Tree_Item>(wdg);
        if (!item) {
            return;
        }
        item->m_level = m_level + 1;
        Frtk_GrpWidget::addChild(item);
    }

    int Frtk_Tree_Item::handle(int events)
    {
        auto key = m_mainWindow->m_sysEvents.keyB;
        switch (events) {
        case FR_LEFT_PUSH:
            m_draggin = false;
            if (isPluseClicked()) {
                if (!(key.ctrlDown || key.shiftDown)) {
                    clearFocusAll();
                }
                m_open = !m_open;
                if (!m_open) {
                    clearFocusAll();
                }
                do_callback();
                return 1;
            }
            else if (isItemClick()) {
                if (!(key.ctrlDown || key.shiftDown)) {
                    clearFocusAll();
                }
                focus(true);
                return 1;
            }
            else {
                if (!(key.ctrlDown || key.shiftDown)) {
                    clearFocusAll();
                }
            }
            break;

        case FR_LEFT_DRAG_PUSH: {
            if (key.shiftDown) {
                m_draggin = true;
                if (!(key.ctrlDown)) {
                    clearFocusAll();  // clear non-ctrl shift-drag
                }
                if (isItemClick()) {
                    focus(true);
                    return 1;
                }
            }
            break;
        }

        case FR_LEFT_DRAG_MOVE: {
            if (m_draggin && key.shiftDown && isItemClick()) {
                focus(true);
                return 1;
            }
            break;
        }

        case FR_LEFT_RELEASE: {
            m_draggin = false;
            break;
        }
        }

        if (hasChildren() && m_open) {
            for (auto& child : m_children) {
                std::shared_ptr<Frtk_Tree_Item> item =
                    std::dynamic_pointer_cast<Frtk_Tree_Item>(child);
                if (item) {
                    if (m_draggin) item->m_draggin = true;
                    if (item->handle(events))
                        return 1;
                }
            }
        }
        return 0;
    }
}