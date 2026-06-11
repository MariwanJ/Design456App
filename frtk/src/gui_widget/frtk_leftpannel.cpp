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
#include <gui_widget/frtk_vwin.h>
#include <glm/gtx/string_cast.hpp>
#include <Math/fr_math.h>
#include <fr_constants.h>
#include <cstdlib>
#include <ctime>
#include <fr_basic_shapes.h>
#include <gui_widget/frtk_tab.h>
#include <gui_widget/frtk_button.h>
#include <gui_widget/frtk_tree.h>
#include <gui_widget/frtk_tree_item.h>
#include <gui_widget/frtk_leftpannel.h>
#include <fr_menu.h>

namespace FR {
    static void cb_BasicShapes(Frtk_LeftPanel* w, size_t index) {
        if (!w || !w->m_linkToMainWindow) {
            FRTK_CORE_FATAL("Could not find a windows instances, Basic Shape callback");
            return;
        }
        srand(time(nullptr));
        auto win = w->m_linkToMainWindow;
        std::string nr = std::to_string(rand() % 10001); // 0-10000
        switch (index) {
        case PART_BOX: {
            std::string content(reinterpret_cast<char*>(cube_off), cube_off_len);
            win->activeScene->add3DObject(content, std::string("Cube") + nr);
        } break;
        case PART_CONE: {
            std::string content(reinterpret_cast<char*>(cone_off), cone_off_len);
            win->activeScene->add3DObject(content, std::string("Cone") + nr);
        } break;
        case PART_CYLINDER: {
            std::string content(reinterpret_cast<char*>(cylinder_off), cylinder_off_len);
            win->activeScene->add3DObject(content, std::string("Cylinder") + nr);
        } break;
        case PART_ELLIPSOID: {
            std::string content(reinterpret_cast<char*>(ellipsoid_off), ellipsoid_off_len);
            win->activeScene->add3DObject(content, std::string("ellipsoid") + nr);
        } break;
        case PART_PRISM: {
            std::string content(reinterpret_cast<char*>(prism_off), prism_off_len);
            win->activeScene->add3DObject(content, std::string("Prism") + nr);
        } break;
        case PART_PYRAMID: {
            std::string content(reinterpret_cast<char*>(pyramid_off), pyramid_off_len);
            win->activeScene->add3DObject(content, std::string("Pyramid") + nr);
        } break;
        case PART_SPHERE: {
            std::string content(reinterpret_cast<char*>(sphere_off), sphere_off_len);
            win->activeScene->add3DObject(content, std::string("Sphere") + nr);
        } break;
        case PART_TORUS: {
            std::string content(reinterpret_cast<char*>(torus_off), torus_off_len);
            win->activeScene->add3DObject(content, std::string("Torus") + nr);
        } break;
        case PART_TUBE: {
            std::string content(reinterpret_cast<char*>(tube_off), tube_off_len);
            win->activeScene->add3DObject(content, std::string("Tube") + nr);
        } break;
        case PART_WEDGE: {
            std::string content(reinterpret_cast<char*>(wedge_off), wedge_off_len);
            win->activeScene->add3DObject(content, std::string("Wedge") + nr);
        } break;
        }
    }
    void Frtk_LeftPanel::updateTree() {
        auto win = m_linkToMainWindow;
        std::shared_ptr< Frtk_Tree_Item > root = std::dynamic_pointer_cast<Frtk_Tree_Item> (m_modelTree->getChildren()[0]);
        auto children = root->getChildren();
        for (auto wdg : m_linkToMainWindow->activeScene->m_world) {
            bool found = false; 
            for (size_t i = 0; i < children.size(); ++i) {
                std::shared_ptr<Frtk_Tree_Item> itempntr = std::dynamic_pointer_cast<Frtk_Tree_Item> (children[i]);
                FRTK_CORE_INFO("item id {}  wdg id {}", itempntr->id, wdg.id);
                if(itempntr)
                    if (itempntr->id == wdg.id) {
                        found = true; 
                        break;
                    }   
            }
            if (!found) {
                if (!(wdg.name == "Sun" || wdg.name == "Grid" || wdg.name == "Axis3D")) {
                    std::shared_ptr<Frtk_Tree_Item> nItem = std::make_shared<Frtk_Tree_Item>(m_vg, 0.0f, 0.0f, 0.0f, 0.0f, wdg.name);
                    nItem->id = wdg.id;
                    auto root= std::dynamic_pointer_cast<Frtk_Tree_Item> (m_modelTree->getChildren()[0]);
                    root->addChild(nItem);
                }
            }
        }
    }

    void Frtk_LeftPanel::draw_focus()
    {
        //Here focus should be drawn in another way. At the moment we do nothing 
        //TODO: FIX ME : 2026-06-01
    }

    void Frtk_LeftPanel::setupModel() {
        auto cx = m_vg;
        m_modelTree = std::make_shared<Frtk_Tree>(cx, 5.0f, 5.0f, m_w - 5.0f, m_h * 0.5f - 5.0f, "", FRTK_DOWN_BOX);
        m_modelTree->color(FR_WHITE);
        auto root = std::make_shared<Frtk_Tree_Item>(cx, 0, 0, 0, 0, "Scene World");
        root->Open(true);
        root->itemType(FRTK_TREE_ITEM_ROOT);
        m_modelTree->addChild(root);
        for (auto obj : m_linkToMainWindow->activeScene->m_world) {
            if (!(obj.name == "Sun" || obj.name == "Grid" || obj.name == "Axis3D")) {
                auto item = std::make_shared<Frtk_Tree_Item>(cx, 0, 0, 0, 0, obj.name);
                item->itemType(FRTK_TREE_ITEM_MIDDLE);
                root->addChild(item);
            }
        }
        m_Model->addChild(m_modelTree);
    }

    Frtk_LeftPanel::Frtk_LeftPanel(float X, float Y, float W, float H, std::string lbl, BOX_TYPE b, bool hasHeader) : Frtk_Vwin(X, Y, W, H, lbl, b, hasHeader)
    {
        Dim_float_t dim = { {0.0f, 28.0f },{400, h() - 28.f} };
        std::shared_ptr<Frtk_Vwin> leftPanel = std::make_shared<Frtk_Vwin>(dim.pos.x, dim.pos.y, dim.size.w, dim.size.h, "");
        leftPanel->hasHeader(false);
        auto cx = leftPanel->getContext();
        m_mainTab = std::make_shared<Frtk_Tabs>(cx, 0.0f, 0.0f, leftPanel->w(), leftPanel->h() / 2, "Main");

        m_Model = m_mainTab->addTab();
        m_Model->label("Model");
        m_Model->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        m_Basic = m_mainTab->addTab();
        m_Basic->label("Basic Shapes");
        m_Basic->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        auto advanced_shapes = m_mainTab->addTab();
        advanced_shapes->label("Advanced Shapes");
        advanced_shapes->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        addChild(m_mainTab);
        setupBasicShapes();
        setupModel();
    }

    std::shared_ptr<Frtk_Tree> Frtk_LeftPanel::getModelTree() {
        return m_modelTree;
    }
    std::shared_ptr<Frtk_Tabwdg> Frtk_LeftPanel::getModel() {
        return m_Model;
    }

    void Frtk_LeftPanel::setupBasicShapes() {
        // Add Basic shape buttons:
        const float hPadding = 10.0f;
        const float vPadding = 10.0f;
        const float btnSize = 40.0f;
        const float startX = 5.0f;
        const float startY = 5.0f;
        const int   cols = 5;
        for (int i = 0; i < static_cast<int>(icons.size()); ++i) {
            int   col = i % cols;
            int   row = i / cols;
            float x = startX + col * (btnSize + hPadding);
            float y = startY + row * (btnSize + vPadding);

            auto btn = std::make_shared<Frtk_Button>(m_vg, x, y, btnSize, btnSize, "");

            btn->set_callback([this, i](Frtk_Widget& w) { cb_BasicShapes(this, i); });
            btn->wdgImage(iconPath + icons.at(static_cast<BASIC_ICONS>(i)));
            m_Basic->addChild(btn);
        }
    }
}