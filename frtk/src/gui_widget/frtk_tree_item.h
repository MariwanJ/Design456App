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

#ifndef Frtk_Tree_Item_ITEM_H
#define Frtk_Tree_Item_ITEM_H
#include <frtk.h>
#include <fr_core.h>
#include <gui_widget/frtk_grpwidget.h>

namespace FR {

    typedef struct  {
        float Hpadding; 
        float Vpadding;
        float itemHeight; 
        float halfVline;
        float hArm;
        float lineWidth;
        Dim_float_t toggleIcon;
        NVGcolor lineColor;
        NVGcolor bgColor;
        NVGcolor selColor;
    }treeStyle_t;
    
    typedef enum {
        TREE_ITEM_CLOSED = 0,
        TREE_ITEM_OPEN = 1,
        TREE_ITEM_PAPER = 2,
    }iconType_t;


    typedef enum {
        FRTK_TREE_ITEM_NONE,   
        FRTK_TREE_ITEM_ROOT,  // top of the tree
        FRTK_TREE_ITEM_MIDDLE,// middle of siblings
        FRTK_TREE_ITEM_TAIL,  // last of siblings
    } treeItemtype_t;

    class Frtk_Tree_Item  : public Frtk_GrpWidget
    {
        friend class Frtk_Tree;
    public:
        Frtk_Tree_Item(NVGcontext* vg, float X, float Y, float W, float H, std::string label = "", BOX_TYPE b = FRTK_NO_BOX);
        virtual ~Frtk_Tree_Item();
        bool isOpen(void);
        bool isTail();
        bool isRoot() const;
        virtual bool hasChildren() override;
        virtual void itemType(treeItemtype_t type);
        treeItemtype_t itemType();
        virtual void clearFocusAll() override;
        virtual void addChild(std::shared_ptr<Frtk_Widget> wdg) override;

    protected:
        Frtk_Tree_Item* getRoot() const;

        virtual void draw() override;
        virtual void updateChildren();

        //Widget Icon/image
        virtual int wdgImage(std::string path, std::optional<glm::vec4> tint = std::nullopt) override;
        virtual int wdgImage(const std::vector<uint8_t>& pngData, std::optional<glm::vec4> tint = std::nullopt) override;

        virtual void drawImage(Dim_float_t dim) override;
        virtual void drawImage() override;
        virtual void drawImage(float x, float y, float w, float h) override;


        virtual void draw_focus() override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H) override;
        virtual void draw_focus(BOX_TYPE t, float X, float Y, float W, float H, glm::vec4 bkg) override;

        virtual void drawNode();
        virtual void drawIconBox();
        virtual void drawBackground();
        
        int getWidth();
        int getSubtreeWidth();

        bool isPluseClicked();
        bool isItemClick();

        virtual int handle (int events) override;
        treeItemtype_t m_itemType;
        treeStyle_t m_style;
        int m_level;
        int m_selected;
        bool m_open;
        bool m_draggin;
    private:
        float m_cachedWidth;
        bool m_dirty;
    };
}

#endif // Frtk_Tree_Item_ITEM_H



