#ifndef FR_IMGUILAYER_H
#define FR_IMGUILAYER_H
#include <../src/Fr_Core.h>

class FRTK_API Fr_ImGuiLayer {
public:
    Fr_ImGuiLayer();
    ~Fr_ImGuiLayer();
    void createLayer();
    void destroyLayer();

    void StartLayer();
    void EndLayer();
};
#endif // !FR_IMGUILAYER_H
