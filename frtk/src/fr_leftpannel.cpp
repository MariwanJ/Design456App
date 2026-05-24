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

#include <fr_window.h>
#include <gui_widget/frtk_vwin.h>
#include <gui_widget/frtk_toolbar_vwin.h>
#include<fr_menu.h>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
#include <gui_widget/frtk_tab.h>
#include <gui_widget/frtk_button.h>
#include <fr_basic_shapes.h>
#include <gui_widget/frtk_tree.h>
#include <gui_widget/frtk_tree_item.h>

namespace FR {
    typedef enum {
        PART_BOX = 0,
        PART_CONE,
        PART_CYLINDER,
        PART_ELLIPSOID,
        PART_PRISM,
        PART_PYRAMID,
        PART_SPHERE = 6,
        PART_TORUS = 7,
        PART_TUBE,
        PART_WEDGE,
    }BASIC_ICONS;

    static std::map<BASIC_ICONS, std::string> icons = {
        { PART_BOX,       "/48x48/Part_Box.png"       },
        { PART_CONE,      "/48x48/Part_Cone.png"      },
        { PART_CYLINDER,  "/48x48/Part_Cylinder.png"  },
        { PART_ELLIPSOID, "/48x48/Part_Ellipsoid.png" },
        { PART_PRISM,     "/48x48/Part_Prism.png"     },
        { PART_PYRAMID,   "/48x48/Part_Pyramid.png"   },
        { PART_SPHERE,    "/48x48/Part_Sphere.png"    },
        { PART_TORUS,     "/48x48/Part_Torus.png"     },
        { PART_TUBE,      "/48x48/Part_Tube.png"      },
        { PART_WEDGE,     "/48x48/Part_Wedge.png"     },
    };

    static void cb_BasicShapes(Fr_Window* w, size_t index) {
        switch (index) {
        case PART_BOX: {
            std::string content(reinterpret_cast<char*>(cube_off), cube_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_CONE: {
            std::string content(reinterpret_cast<char*>(cone_off), cone_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_CYLINDER: {
            std::string content(reinterpret_cast<char*>(cylinder_off), cylinder_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_ELLIPSOID: {
            std::string content(reinterpret_cast<char*>(ellipsoid_off), ellipsoid_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_PRISM: {
            std::string content(reinterpret_cast<char*>(prism_off), prism_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_PYRAMID: {
            std::string content(reinterpret_cast<char*>(pyramid_off), pyramid_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_SPHERE: {
            std::string content(reinterpret_cast<char*>(sphere_off), sphere_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_TORUS: {
            std::string content(reinterpret_cast<char*>(torus_off), torus_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_TUBE: {
            std::string content(reinterpret_cast<char*>(tube_off), tube_off_len);
            w->activeScene->add3DObject(content);
        } break;
        case PART_WEDGE: {
            std::string content(reinterpret_cast<char*>(wedge_off), wedge_off_len);
            w->activeScene->add3DObject(content);
        } break;
        }
        w->updateModelTab();
    }
    void Fr_Window::setupModel(std::shared_ptr<Frtk_Vwin> leftpanel, std::shared_ptr<Frtk_Tabwdg> model) {
        auto cx = leftpanel->getContext();
        std::shared_ptr<Frtk_Tree> tree = std::make_shared<Frtk_Tree>(cx, 5.0f, 5.0f, leftpanel->w() - 5.0f, leftpanel->h() / 2 - 5.0f, "", FRTK_DOWN_BOX);
        tree->color(FR_WHITE);
        auto root = std::make_shared<Frtk_Tree_Item>(cx, 0, 0, 0, 0, "Scene World");
        root->itemType(FRTK_TREE_ITEM_ROOT);
        tree->addChild(root);
        for (auto obj : activeScene->m_world) {
            if (!(obj.name == "Sun" || obj.name == "Grid" || obj.name == "Axis3D")) {
                auto item = std::make_shared<Frtk_Tree_Item>(cx, 0, 0, 0, 0, obj.name);
                item->itemType(FRTK_TREE_ITEM_MIDDLE);
                root->addChild(item);
            }
        }
        model->addChild(tree);
    }
    void Fr_Window::updateModelTab()

    {
        std::shared_ptr<Frtk_Tabs> tabs = std::static_pointer_cast<Frtk_Tabs>(m_leftPanel->m_guiWindow->getChildren()[0]);
        std::shared_ptr<Frtk_Tabwdg> model_tab = std::static_pointer_cast<Frtk_Tabwdg>(tabs->getChildren()[0]);
        std::shared_ptr<Frtk_Tree> tree = std::static_pointer_cast<Frtk_Tree>(model_tab->getChildren()->getChildren()[0]);
        auto cx = m_leftPanel->getContext();
        for (auto& worldItem : activeScene->m_world)
        {
            bool exists = false;

            for (auto& child : tree->getChildren())
            {
                if (child->label() == worldItem.name)
                {
                    exists = true;
                    break;
                }

                if (!exists)
                {
                    if (worldItem.name != "Sun" &&
                        worldItem.name != "Grid" &&
                        worldItem.name != "Axis3D") {
                        auto nItem = std::make_shared<Frtk_Tree_Item>(cx, 0.0f, 0.0f, 0.0f, 0.0f, worldItem.name);
                        tree->addChild(nItem);
                    }
                }
            }
        }
    }

    void Fr_Window::setupBasicShapes(std::shared_ptr<Frtk_Vwin> leftpanel, std::shared_ptr<Frtk_Tabwdg> basic) {
        // Add Basic shape buttons:
        const float hPadding = 10.0f;
        const float vPadding = 10.0f;
        const float btnSize = 40.0f;
        const float startX = 5.0f;
        const float startY = 5.0f;
        const int   cols = 5;

        auto cx = leftpanel->getContext();

        for (int i = 0; i < static_cast<int>(icons.size()); ++i) {
            int   col = i % cols;
            int   row = i / cols;
            float x = startX + col * (btnSize + hPadding);
            float y = startY + row * (btnSize + vPadding);

            auto btn = std::make_shared<Frtk_Button>(cx, x, y, btnSize, btnSize, "");

            btn->set_callback([this, i](Frtk_Widget& w) { cb_BasicShapes(this, i); });
            btn->wdgImage(iconPath + icons.at(static_cast<BASIC_ICONS>(i)));
            basic->addChild(btn);
        }
    }

    std::shared_ptr<Frtk_Vwin> Fr_Window::leftPanel()
    {
        Dim_float_t dim = { {0.0f, 28.0f },{400, h() - 28.f} };
        std::shared_ptr<Frtk_Vwin> leftPanel = std::make_shared<Frtk_Vwin>(dim.pos.x, dim.pos.y, dim.size.w, dim.size.h, "");
        leftPanel->hasHeader(false);
        auto cx = leftPanel->getContext();
        auto m_leftPanelTab = std::make_shared<Frtk_Tabs>(cx, 0.0f, 0.0f, leftPanel->w(), leftPanel->h() / 2, "Main");

        auto model = m_leftPanelTab->addTab();
        model->label("Model");
        model->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        auto basic = m_leftPanelTab->addTab();
        basic->label("Basic Shapes");
        basic->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        auto advanced_shapes = m_leftPanelTab->addTab();
        advanced_shapes->label("Advanced Shapes");
        advanced_shapes->lblAlign(NVG_ALIGN_TOP_CENTER | NVG_ALIGN_BASELINE | NVG_ALIGN_INSIDE);

        leftPanel->addChild(m_leftPanelTab);
        setupBasicShapes(leftPanel, basic);
        setupModel(leftPanel, model);
        return leftPanel;
    }
}