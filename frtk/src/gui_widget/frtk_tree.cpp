#include "frtk_tree.h"
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

#include <gui_widget/frtk_tree.h>
#include<gui_widget/frtk_tree_item_icn.h>

namespace FR {
    Frtk_Tree::Frtk_Tree(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b) : Frtk_GrpWidget(vg, X, Y, W, H, lbl, b)
    {
        m_vg = vg;
        m_wdgType = FRTK_TREE_WIDGET;
        initIcons();
    }
    void Frtk_Tree::initIcons()
    {
        std::array<const std::vector<uint8_t>*, 3> sources = {
            &folder_icon1, &folder_icon2, &doc_icon
        };

        for (const auto* src : sources)
        {
            FRTK_CORE_APP_ASSERT(src && !src->empty(), "Invalid icon source");
            iconImageSize_t item;
            int w = 0, h = 0;
            unsigned char* decoded = stbi_load_from_memory(src->data(), static_cast<int>(src->size()), &w, &h, nullptr, 4);
            FRTK_CORE_APP_ASSERT(decoded, "Failed to decode icon");
            item.texture = nvgCreateImageRGBA(m_vg, w, h, 0, decoded);
            if (!item.texture) {
                stbi_image_free(decoded);
                FRTK_CORE_APP_ASSERT(false, "Failed to create texture");
            }
            item.dim.size.w = static_cast<float>(w);
            item.dim.size.h = static_cast<float>(h);
            item.opacity = 1.0f;
            stbi_image_free(decoded);
            defaultIcons.emplace_back(std::move(item));
        }
    }

    GLuint Frtk_Tree::getIconTexture(iconType_t type) const {
        return defaultIcons[static_cast<int>(type)].texture;
    }

    std::shared_ptr<Frtk_Tree_Item> Frtk_Tree::rootWdg()
    {
        if (m_children.size() > 0)
            return std::dynamic_pointer_cast<Frtk_Tree_Item>(m_children[0]); //first item is the root
        return nullptr;
    }
    void Frtk_Tree::addChild(std::shared_ptr<Frtk_Widget> wdg)
    {
        //Only root and level 1 is added by this (addChild) function
        auto item = std::dynamic_pointer_cast<Frtk_Tree_Item>(wdg);
        if (!item) {
            return;
        }
        if (m_children.empty()) {
            item->m_level = -1; // root
            Frtk_GrpWidget::addChild(wdg);
            return;
        }
        auto root = std::dynamic_pointer_cast<Frtk_Tree_Item>(m_children[0]);
        /*This should always be the case, all children
            added to the tree in the
            first level should become a child of root*/
        root->addChild(wdg);
    }

    void Frtk_Tree::draw()
    {
        draw_box(m_vg, m_boxType, { {m_x, m_y}, {m_w, m_h} }, m_cornerRadius, FRTK_NORMAL_BORDER, glmToNVG(m_color), glmToNVG(m_bkg_color), true);
        layoutItems();
        nvgSave(m_vg);
        nvgTranslate(m_vg, m_x, m_y);
        draw_children();
        nvgRestore(m_vg);
    }
    void Frtk_Tree::draw_children() {
        std::shared_ptr<Frtk_Tree_Item> item = std::dynamic_pointer_cast<Frtk_Tree_Item> (m_children[0]);
        item->draw();
    }

    void Frtk_Tree::updateTree()
    {
        if (m_children.empty())
            return;
        auto root = std::dynamic_pointer_cast<Frtk_Tree_Item>(m_children[0]);
        if (!root)
            return;
        root->m_level = -1;
        root->updateChildren();
        layoutItems();
    }

    void Frtk_Tree::layoutItems()
    {
        auto root = std::dynamic_pointer_cast<Frtk_Tree_Item>(m_children[0]);
        if (!root)
            return;
        layoutItem(root, root->m_style.Vpadding, 0);
    }
    float Frtk_Tree::layoutItem(std::shared_ptr<Frtk_Tree_Item> item, float currentY, int level)
    {
        if (!item)
            return currentY;

        item->m_level = level;
        if (level == 0)
            item->x(item->m_style.Hpadding);
        else{
            item->x(item->m_style.Hpadding + item->m_style.hArm);
        }
        item->y(currentY);
        item->w(m_w);
        item->h(item->m_style.itemHeight);
        float y = item->m_style.itemHeight;
        if (item->isOpen())
        {
            for (auto& child_base : item->m_children)
            {
                auto child = std::dynamic_pointer_cast<Frtk_Tree_Item>(child_base);
                if (child)
                {
                    child->y(y);          // relative below parent
                    y = layoutItem(child, child->y(), level + 1);
                }
            }
        }
        return currentY + y;
    }

    std::vector<std::shared_ptr<Frtk_Tree_Item>> Frtk_Tree::getSelectedItems() {
        std::vector<std::shared_ptr<Frtk_Tree_Item>> items;
        collectSelected(m_children, items);
        return items;
    }

    void Frtk_Tree::collectSelected(const std::vector<std::shared_ptr<Frtk_Widget>>& children, std::vector<std::shared_ptr<Frtk_Tree_Item>>& items) {
        for (auto& child : children) {
            auto item = std::dynamic_pointer_cast<Frtk_Tree_Item>(child);
            if (!item) continue;
            if (item->has_focus()) {
                items.emplace_back(item);
            }
            if (item->hasChildren() && item->isOpen()) {
                collectSelected(item->getChildren(), items);
            }
        }
    }

    // Helper: recursively send event to an item and all its descendants
    int Frtk_Tree::dispatch_to_item(Frtk_Tree_Item* item, int ev)
    {
        if (!item) return 0;
        if (item->handle(ev) == 1)
            return 1;

        for (size_t i = 0; i < item->m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tree_Item> child =
                std::dynamic_pointer_cast<Frtk_Tree_Item>(item->m_children[i]);
            if (child && dispatch_to_item(child.get(), ev) == 1)
                return 1;
        }
        return 0;
    }

    int Frtk_Tree::handle(int ev)
    {
        for (size_t i = 0; i < m_children.size(); ++i) {
            std::shared_ptr<Frtk_Tree_Item> it =
                std::dynamic_pointer_cast<Frtk_Tree_Item>(m_children[i]);
            if (it && dispatch_to_item(it.get(), ev) == 1)
                return 1;
        }
        return 0;
    }
}