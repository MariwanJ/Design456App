#ifndef FR_WINDOW_H
#define FR_WINDOW_H
#include <ThreeDWidgets/fr_wgroup.h>

class Fr_Window : public FR_GROUP_WIDGET {
    Fr_Window(glm::vec3 position, std::shared_ptr<std::vector <float>> verticies, std::shared_ptr<std::vector <float>> indicies, std::string label);
};

#endif // !FR_WINDOW_H
