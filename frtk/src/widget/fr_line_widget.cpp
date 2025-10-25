//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
#include <widget/fr_line_widget.h>
#include <glm/gtx/transform.hpp>
#include <fr_window.h>
namespace FR {
    Fr_Line_Widget::Fr_Line_Widget(std::shared_ptr<std::vector <float>> verticies,
        std::shared_ptr<std::vector <unsigned int>> indicies,
        std::string label) : Fr_Widget(verticies, indicies, label),m_pointPicker(false)
    {
        m_normals = std::make_shared<std::vector<float>>();
        m_textCoord = std::make_shared<std::vector<float>>();
        
        // Add vertices and store their handles
        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            MyMesh::Point p(m_vertices->at(i), m_vertices->at(i+ 1), m_vertices->at(i + 2) );
            MyMesh::VertexHandle vh = m_mesh.add_vertex(p);
        }

        /*
        Notice that:
            if you dont have faces, you dont get edges from open mesh. 
            So, if you want to create a face from the edges, you have to rebuild the entire thing
        */
        CalculateNormals();
        lineWidth(1);
        std::vector<MyMesh::VertexHandle> vertexHandles;
        m_WidgType = NODETYPE::FR_LINE_WIDGET;
        m_lineType = FR_LINES;
        initializeVBO();
        CreateShader();
        m_boundBox = std::make_shared<cBoundBox3D>();
        m_boundBox->setVertices(m_vertices);

    }

    Fr_Line_Widget::~Fr_Line_Widget()
    {
    }

    void Fr_Line_Widget::draw()
    {
        draw_2d();
    }

    void Fr_Line_Widget::draw_points()
    {
        DrawPoints();
    }


    void Fr_Line_Widget::redraw()
    {
        CalculateNormals();
        initializeVBO();
        draw_2d();
    }

    void Fr_Line_Widget::lbl_draw()
    {
        //  lineObj->Draw();
    }

    void Fr_Line_Widget::lbl_redraw()
    {
        lbl_draw();
    }

    void Fr_Line_Widget::pointPicker(bool val)
    {
        m_pointPicker = val;
    }
    bool Fr_Line_Widget::pointPicker()
    {
        return m_pointPicker;
    }

    void Fr_Line_Widget::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
        unsigned int nlights = std::min(lights.size(), kMaxLights);
        program->SetUniformInteger("nlights", nlights);
        for (size_t i = 0; i < nlights; ++i) {
            auto uniformVarNameInObjShader = "lights[" + std::to_string(i) + "].";
            program->SetUniformVec4(uniformVarNameInObjShader + "color", lights[i].lightcolor);
            program->SetUniformVec4(uniformVarNameInObjShader + "position", lights[i].position);       //Here we send the name of the variable as "lights[xxx=number]." wher xxx= a number from 0 to nlights
            program->SetUniformVec4(uniformVarNameInObjShader + "diffuse", lights[i].diffuse);
            program->SetUniformVec4(uniformVarNameInObjShader + "specular", lights[i].specular);
            program->SetUniformVec4(uniformVarNameInObjShader + "ambient", lights[i].ambient);
            program->SetUniformVec3(uniformVarNameInObjShader + "attenuation", lights[i].attenuation);
            program->SetUniformInteger(uniformVarNameInObjShader + "is_spot", lights[i].is_spot);
            program->SetUniformVec3(uniformVarNameInObjShader + "direction", lights[i].direction);
            program->SetUniformFloat(uniformVarNameInObjShader + "cutoff", lights[i].cutoff);
            program->SetUniformFloat(uniformVarNameInObjShader + "exponent", lights[i].exponent);
        }
        program->SetUniformCamPosition("camPos");

    }
    void Fr_Line_Widget::RenderVertexes(RenderInfo& info) {
        if (!m_active)
            return;
        auto mvp = info.projection * info.modelview * m_Matrix;
        m_shader->widgPoits_prog->Enable();
        m_shader->widgPoits_prog->SetAttribLocation("position", 0);
        m_shader->widgPoits_prog->SetAttribLocation("selected", 1); // depending on the status, it will give yellow color or color
        m_shader->widgPoits_prog->SetUniformMat4("mvp", mvp);
        m_shader->widgPoits_prog->SetUniformVec4("color", m_color);
        m_shader->widgPoits_prog->SetUniformFloat("pointSize", pointSize());
        draw_points();
        m_shader->widgPoits_prog->Disable();
    }
    void Fr_Line_Widget::Render(RenderInfo& info) {
        if (!m_active)
            return;

        auto mvp = info.projection * info.modelview * m_Matrix;
        auto normalmatrix = glm::transpose(glm::inverse(info.modelview));
        m_shader->wdg_prog->Enable();
        LoadLights(m_shader->wdg_prog, info.lights);
        m_shader->wdg_prog->SetAttribLocation("position", POSITION_VERTEX_VB);  //Position variable has (layout(location =0) inside vs shader
        m_shader->wdg_prog->SetAttribLocation("texCoord", POSITION_TEXCOORD_VB);  //Position variable has (layout(location =1 inside vs shader
        m_shader->wdg_prog->SetAttribLocation("normal", POSITION_NORMAL_VB);  //Position variable has (layout(location =1 inside vs shader
        m_shader->wdg_prog->SetUniformMat4("modelview", info.modelview);
        m_shader->wdg_prog->SetUniformMat4("normalmatrix", normalmatrix);
        m_shader->wdg_prog->SetUniformMat4("mvp", mvp);
        m_shader->wdg_prog->SetUniformVec4("color", m_color);       //Object color - not light color
        m_shader->wdg_prog->SetUniformInteger("hasTexture", false);
        draw();      //You should make a draw call to get that  done
        lbl_draw();
        m_shader->wdg_prog->Disable();
        info.id++;
        RenderVertexes(info);
    }

    int Fr_Line_Widget::handle(int e)
    {
        if (!m_active)
            return 0; //we don't use the event/we don't care

        Fr_Window* win = Fr_Window::getFr_Window();
        ray_t mouseworld = win->GetScreenToWorldRay();
        

        win->RayMousePos[0] = mouseworld.position;
        win->RayMousePos[1] = win->calculateMouseRay();//mouseworld.direction;

        if (m_pointPicker) {
            /*
            Here mouse will pick points that will be added to the line points.
            Here also we should allow to move the point. If Key Enter is not pressed, the last point will continue to move
            to finish this process, user should press ESC key After entering the amount of points user desire
            */
            //TODO: Should we change the cursor image?

            unsigned int lastValue = m_vertices->size();
            switch (e) {
            case FR_MOUSE_MOVE: {
                //Mouse move without clicking or entering key ..
                //NOT IMPLEMENTED
                ray_t ray = win->GetScreenToWorldRay();
 
                glm::vec3 intersectionPoint;
                //intersectVertexIn3D
               // intersectionChecker
                glm::vec3 next = ray.direction * 1000.0f;
                glm::vec3 p1= glm::vec3(m_vertices->at(0), m_vertices->at(1), m_vertices->at(2));
                glm::vec3 p2 = glm::vec3(m_vertices->at(3), m_vertices->at(4), m_vertices->at(5));
                //Point picker
                if(intersectPointIn3D(ray,p1, 5.0f) || intersectPointIn3D(ray, p2, 5.0f))
                {
                        SetColor(glm::vec4(FR_ORANGERED));
                        lineWidth(3);
                        break;
                    }
                else{
                    lineWidth(1);
                    SetColor(glm::vec4(FR_ANTIQUEWHITE));
                }
                return 0;//
            }
                              break;

            case  FR_LEFT_PUSH: {
                //DRAG THE OBJECT .. TODO : HOW SHOULD WE DO THAT???

                //Start to pick, or move the point position
                ray_t ray = win->GetScreenToWorldRay();
                glm::vec3 np = win->calculateMouseWorldPos();
                glm::vec3 next = ray.direction * 1000.0f;
                bool result;
                glm::vec3 intersectionPoint;
                glm::vec3 p1 = glm::vec3(m_vertices->at(0), m_vertices->at(1), m_vertices->at(2));
                glm::vec3 p2 = glm::vec3(m_vertices->at(3), m_vertices->at(4), m_vertices->at(5));
                result = (intersectPointIn3D(ray, p1, 5.0f) || intersectPointIn3D(ray, p2, 5.0f));
                if (result) {
                    //TODO This is not correct FIXME
                    m_vertices->at(0) = np.x;//ray.direction.x;
                    m_vertices->at(1) = np.y;//ray.direction.y;
                    m_vertices->at(2) = np.z;//ray.direction.z;

                    redraw();
                }
                return 1;//Consume the event.
            } break;

            case FR_KEYBOARD: {
                eventData keyEvent = win->GLFWevents();
                if (keyEvent.lastKey == GLFW_KEY_E) {
                    m_pointPicker = false;
                    redraw();
                }
            }
                            break;
            case FR_LEFT_DRAG_PUSH: {
                //This should select the item -- not implemented yet
            }
                                  break;
            }
            return 0;
        }
        return 0;
    }
}