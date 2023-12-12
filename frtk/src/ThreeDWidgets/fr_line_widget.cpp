#include "fr_line_widget.h"
namespace FR{
Fr_Line_Widget::Fr_Line_Widget(glm::vec3 position, std::shared_ptr<std::vector <float>> verticies,
                                     std::shared_ptr<std::vector <float>> indicies, std::string label):
                                     Fr_Widget(position,verticies,indicies,label)
{
}

Fr_Line_Widget::~Fr_Line_Widget()
{
}

void Fr_Line_Widget::draw()
{
}

void Fr_Line_Widget::lbl_draw()
{
}

void Fr_Line_Widget::lbl_redraw()
{
}
}