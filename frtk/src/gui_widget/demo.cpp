#include<gui_widget/demo.h>

#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_button.h>
#include <gui_widget/frtk_toolbar.h>
#include <gui_widget/frtk_toolbar_button.h>

namespace FR {
    std::shared_ptr<Frtk_Window> runFRTKdemo() {
        /*
          boxtypes:
          =========
                FRTK_NO_BOX = 0,
                FRTK_FLAT_BOX,
                FRTK_DOWN_BOX,
                FRTK_UP_BOX,
                FRTK_UP_FRAME,
                FRTK_DOWN_FRAME,
                FRTK_THIN_UP_BOX,
                FRTK_THIN_DOWN_BOX,
                FRTK_THIN_UP_FRAME,
                FRTK_THIN_DOWN_FRAME,

                FRTK_ROUNDED_BOX,
                FRTK_RSHADOW_BOX,
                FRTK_ROUNDED_FRAME,
                FRTK_RFLAT_BOX,
                FRTK_ROUND_UP_BOX,
                FRTK_ROUND_DOWN_BOX,
                FRTK_DIAMOND_UP_BOX,
                FRTK_DIAMOND_DOWN_BOX,
                FRTK_OVAL_BOX,
                FRTK_OSHADOW_BOX,
                FRTK_OVAL_FRAME,
                FRTK_OVALFLAT_BOX,

        */
        static int counter = 1;
        static int i= 0;
        auto window = std::make_shared<Frtk_Window>(500.f, 200.f, 500.f, 500.f, "Testing FRTK GUI Toolkit");
        std::shared_ptr<Frtk_Box> box;
        std::string imagePath = EXE_CURRENT_DIR + "/resources/icon_48/Home.png";

        float FF, NN;
        FF = NN = 40;
        float next = FF + 5;
        std::shared_ptr<Frtk_Button> button = std::make_shared<Frtk_Button>(window->getContext(), 10.0f, 250.0f, 64.0f, 64.0f, "button", FRTK_UP_BOX);
        button->wdgImage(imagePath);
        window->addChild(button);

       for (int i = 1; i < 4; i++){
            for (int j=0;j<9;j++)
            {
                std::string str= std::to_string(counter);
                box = std::make_shared<Frtk_Box>(window->getContext(), next*j, i * next, FF, NN, str, (BOX_TYPE)counter);
                window->addChild(box);
                counter++;
            }
        } 
       
         return window;
    }
}