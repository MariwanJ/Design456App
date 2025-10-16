#ifndef FR_LINE_WIDGET_H
#define FR_LINE_WIDGET_H

#include <fr_widget.h>
 
namespace FR {
    class FRTK_API Fr_Line_Widget : public Fr_Widget {
    public:
        Fr_Line_Widget(std::shared_ptr<std::vector <float>>verticies,
            std::shared_ptr<std::vector <unsigned int>> indicies,
            std::string label = "");
        virtual ~Fr_Line_Widget();
        //Default constructor is disallowed
        Fr_Line_Widget() = delete;
        virtual void draw();
        void draw_points();
        virtual void redraw() override;

        virtual void lbl_draw();
        virtual void lbl_redraw();

        /**
         * Set if the widget will pick points using mouse.
         *
         * \param val if True, widget will pick points using mouse, if False no picking events will occure
         */
        void pointPicker(bool val);
        /**
         * Get status of widgets point picker variable.
         *
         * \return True if point picker is activated, otherwise false
         */
        bool pointPicker();

    public:
        /**
         * Variable to hold the boundaries of the widgets.
         */

    protected:
        /**
         * Events handler .
         *
         * \param e event value
         * \return 1 if consumed, 0 if not consumed
         */
        int handle(int e) override;
        /**
         * Setup light property for the widget.
         *
         * \param program   Shader program
         * \param lights    Lights info
         */
        void LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights);
        /**
         * Render function which draw the whole widget.
         *
         * \param info
         * \param modelview
         */
        void Render(RenderInfo& info) override;
        /**
         * Render .
         * 
         * \param info
         */
        void RenderVertexes(RenderInfo& info) override;


    private:
        bool m_pointPicker;     //if 1 , mouse will pick points to be added to the polygon(or line)
    };
}

#endif // !FR_LINE_WIDGET
