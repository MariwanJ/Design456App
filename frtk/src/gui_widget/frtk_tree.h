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

#ifndef FRTK_TREE_H
#define FRTK_TREE_H

#include <gui_widget/frtk_tree_item.h>
#include <gui_widget/frtk_grpwidget.h>
#include<frtk.h>
namespace FR {
    class Frtk_Tree : public  Frtk_GrpWidget {
        friend Frtk_Tree_Item;
    public:
        Frtk_Tree(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b);
        std::shared_ptr<Frtk_Tree_Item> rootWdg();
        void updateTree();
        void layoutItems();
        float layoutItem(std::shared_ptr<Frtk_Tree_Item> item, float currentY, int level);
        
        std::vector<std::shared_ptr<Frtk_Tree_Item>> getSelectedItems();
        void collectSelected(const std::vector<std::shared_ptr<Frtk_Widget>>& children, 
                                        std::vector<std::shared_ptr<Frtk_Tree_Item>>& items);
        
        virtual void addChild(std::shared_ptr<Frtk_Widget> wdg) override;
        GLuint getIconTexture(iconType_t type) const;

    protected:
        virtual void draw()  override;
        virtual void draw_children() override;
        int dispatch_to_item(Frtk_Tree_Item* item, int ev);
        virtual int handle(int ev) override;
        std::vector<iconImageSize_t> defaultIcons;
        void initIcons();
    };

}
#endif // FRTK_TREE_H
