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

#ifndef FRTK_LEFTPANEL_H
#define FRTK_LEFTPANEL_H

#include <gui_widget/frtk_vwin.h>
#include <gui_widget/frtk_tab.h>
#include <gui_widget/frtk_tree.h>

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

    class Frtk_LeftPanel : public Frtk_Vwin {
    public:
        Frtk_LeftPanel(float X, float Y, float W, float H, std::string lbl = "", BOX_TYPE b = FRTK_FLAT_BOX, bool hasHeader = true);
        void setupBasicShapes();

        std::shared_ptr<Frtk_Tree> getModelTree();
        std::shared_ptr<Frtk_Tabwdg> getModel();

        //        std::shared_ptr<Frtk_Tabwdg> getBasic();
        //        std::shared_ptr<Frtk_Tabwdg> getAdvanced();
        std::shared_ptr<Frtk_Tree> m_modelTree;
    protected:
        void setupModel();
        std::shared_ptr<Frtk_Tabs> m_mainTab;
        std::shared_ptr<Frtk_Tabwdg> m_Basic;
        std::shared_ptr<Frtk_Tabwdg> m_Advanced;
        std::shared_ptr<Frtk_Tabwdg> m_Model;
    };
}
#endif // FRTK_LEFTPANEL_H