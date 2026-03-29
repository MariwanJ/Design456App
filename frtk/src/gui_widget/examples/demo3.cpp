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

#include<gui_widget/examples/demo3.h>
#include <gui_widget/frtk_slider.h>
#include <gui_widget/frtk_color_picker.h>
#include <gui_widget/frtk_tree.h>
namespace FR {
    //Default callback function.Replace with your custom callback.Arguments are possible.
    static void pickcolor(Frtk_Widget& w, Frtk_Widget& win) {
        auto* wid = dynamic_cast<Frtk_Color_Picker*>(&w);
        glm::vec4 col = wid->pickedColorRGBA();
        win.color(col);
    }

    std::shared_ptr<Frtk_Vwin> runFRTKdemo3() {
        auto window = std::make_shared<Frtk_Vwin>(500.f, 200.f, 500.f, 500.f, "Testing new Widgets");
        std::shared_ptr<Frtk_Slider> sliderH = std::make_shared<Frtk_Slider>(window->getContext(), 275.0f, 250.0f, 200.0f, 56.0f, "SLIDER- H", FRTK_OSHADOW_DOWN_BOX);

        //  sliderH->stepSize(10.0f);
        sliderH->sliderType(H_SLIDER);
        window->addChild(sliderH);

        std::shared_ptr<Frtk_Slider> sliderV = std::make_shared<Frtk_Slider>(window->getContext(), 200.0f, 250.0f, 56.0f, 200.0f, "SLIDER - V", FRTK_UP_BOX);
        sliderV->sliderType(V_SLIDER);
        // sliderV->stepSize(5.0f);
        window->addChild(sliderV);

        std::shared_ptr<Frtk_Color_Picker> col = std::make_shared<Frtk_Color_Picker>(window->getContext(), 10.0f, 10.0f, 200.0f, 200.0f, "colorPicker", FRTK_UP_BOX);
        col->set_callback([window](Frtk_Widget& w) { pickcolor(w, *window); });

        window->addChild(col);

        std::shared_ptr<Frtk_Tree> tree = std::make_shared<Frtk_Tree>(window->getContext(), 290.0f, 10.0f, 200.0f, 200.0f, "Tree", FRTK_UP_BOX);
        std::shared_ptr<Frtk_Tree_Item> root = std::make_shared<Frtk_Tree_Item>(window->getContext(), 0.f, 0.f, 0.f, 0.f, "Root", FRTK_FLAT_BOX);
        root->itemType(FRTK_TREE_ITEM_ROOT);
        tree->addChild(root);

        for (size_t i = 0; i < 10; i++) {
            std::string n= "item "+ std::to_string(i);
            std::shared_ptr<Frtk_Tree_Item> it1 = std::make_shared<Frtk_Tree_Item>(window->getContext(), 0.f, 0.f, 0.f, 0.f, n, FRTK_FLAT_BOX);
            it1->itemType(FRTK_TREE_ITEM_MIDDLE);
            root->addChild(it1);
            for (size_t j = 0; j < 1; j++) {
                std::string n = "sub_item " + std::to_string(i)+ std::to_string(j);
                std::shared_ptr<Frtk_Tree_Item> itt1 = std::make_shared<Frtk_Tree_Item>(window->getContext(), 0.f, 0.f, 0.f, 0.f, n, FRTK_FLAT_BOX);
                itt1->itemType(FRTK_TREE_ITEM_MIDDLE);
                it1->addChild(itt1);
                std::string nn = "sub_sub_item " + std::to_string(i) + std::to_string(j);
                std::shared_ptr<Frtk_Tree_Item> itt2 = std::make_shared<Frtk_Tree_Item>(window->getContext(), 0.f, 0.f, 0.f, 0.f, nn, FRTK_FLAT_BOX);
                itt2->itemType(FRTK_TREE_ITEM_MIDDLE);
                itt1->addChild(itt2);
            }
        }
        window->addChild(tree);
        tree->updateTree();
        return window;
    }
}