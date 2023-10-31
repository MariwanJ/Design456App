#ifndef FR_IMGUILAYER_H
#define FR_IMGUILAYER_H

class Fr_ImGuiLayer {
public:
    Fr_ImGuiLayer();
    ~Fr_ImGuiLayer();
    void createLayer();
    void destroyLayer();

    void StartLayer();
    void EndLayer();
};
#endif // !FR_IMGUILAYER_H
