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
#include "fr_face_widget.h"
#include <glm/gtx/transform.hpp>
#include<fr_window.h>
#include <fr_core.h>
namespace FR {
    Fr_Face_Widget::Fr_Face_Widget(std::shared_ptr<std::vector <float>> vertices,
        std::shared_ptr<std::vector <unsigned int>> indicies,
        std::string label) : Fr_Widget(vertices, indicies, label),m_pointPicker(false)
    {

        std::vector<MyMesh::VertexHandle> vertexHandles;

        // Add vertices and store their handles
        for (size_t i = 0; i < m_vertices->size(); i += 3) {
            MyMesh::Point p(m_vertices->at(i), m_vertices->at(i + 1), m_vertices->at(i + 2));
            MyMesh::VertexHandle vh = m_mesh.add_vertex(p);
            vertexHandles.push_back(vh);
        }

        // create faces (in sets of 3) // TODO: If it is a polygon how to do that???? 
        for (size_t i = 0; i + 2 < vertexHandles.size(); i += 3) {
            m_mesh.add_face(vertexHandles[i], vertexHandles[i + 1], vertexHandles[i + 2]);
        }

        lineWidth(1);
        CalculateNormals();
        initializeVBO();
        CreateShader();
        m_boundBox = std::make_shared<cBoundBox3D>();
        m_boundBox->setVertices(m_vertices);
        m_WidgType = NODETYPE::FR_FACE_WIDGET;
        m_lineType = FR_CLOSED_LOOP;
    }

    Fr_Face_Widget::~Fr_Face_Widget()
    {
    }

    void Fr_Face_Widget::draw()
    {
        draw_2d();
    }

    void Fr_Face_Widget::draw_points()
    {
        DrawPoints();
    }

    void Fr_Face_Widget::redraw()
    {
        CalculateNormals();
       initializeVBO();
        draw_2d();
    }

    void Fr_Face_Widget::lbl_draw()
    {
        //  lineObj->Draw();
    }

    void Fr_Face_Widget::lbl_redraw()
    {
        lbl_draw();
    }

    void Fr_Face_Widget::pointPicker(bool val)
    {
        m_pointPicker = val;
    }
    bool Fr_Face_Widget::pointPicker()
    {
        return m_pointPicker;
    }

    void Fr_Face_Widget::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
        size_t nlights = std::min(lights.size(), kMaxLights);
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
            program->SetUniformCamPosition("camPos");
        }
    }
    void Fr_Face_Widget::RenderVertexes(RenderInfo& info) {
        if (!m_active)
            return;
        auto mvp = info.projection * info.modelview * m_Matrix;
        m_shader->widgPoits_prog->Enable();
        m_shader->widgPoits_prog->SetAttribLocation("position", 0);
        m_shader->widgPoits_prog->SetUniformMat4("mvp", mvp);
        m_shader->widgPoits_prog->SetUniformVec4("color", m_color);
        m_shader->widgPoits_prog->SetUniformFloat("pointSize", pointSize());
        draw_points();
        m_shader->widgPoits_prog->Disable();
    }
    void Fr_Face_Widget::Render(RenderInfo& info) {
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

    int Fr_Face_Widget::handle(int e)
    {
        if (!m_active)
            return 0; //we don't use the event/we don't care

        Fr_Window* win = Fr_Window::getFr_Window();
       /*  if (m_pointPicker)*/ {
            /*
            Here mouse will pick points that will be added to the line points.
            Here also we should allow to move the point. If Key Enter is not pressed, the last point will continue to move
            to finish this process, user should press ESC key After entering the amount of points user desire
            */
            //TODO: Should we change the cursor image?

            size_t lastValue = m_vertices->size();
            switch (e) {
            case FR_MOUSE_MOVE: {
                //Mouse move without clicking or entering key ..
                //NOT IMPLEMENTED
                glm::vec3 nn = win->calculateMouseWorldPos();
                ray_t rtt = win->GetScreenToWorldRay();
                
                //printf("%f %f %f mouse to worl ray +++++++++++++++\n", nn.x, nn.y, nn.z);
                
                win->RayMousePos[0] = rtt.position;
                win->RayMousePos[1] = rtt.direction;
                glm::vec3 intersectionPoint;

                if (win->intersectionChecker(rtt, intersectionPoint)) {
                    FRTK_CORE_INFO("FOUND FACE");
                    SetColor(glm::vec4(FR_BLUE));
                }
                else
                    SetColor(glm::vec4(FR_GREEN)); //FRTK_CORE_INFO("NO FOUND FACE");
            }
            break;

            case  FR_LEFT_PUSH: {
                //DRAG THE OBJECT .. TODO : HOW SHOULD WE DO THAT???

                //Start to pick, or move the point position
                ray_t ray = win->GetScreenToWorldRay();
                //FRTK_CORE_INFO("MOUSE POSITION IN 3D WORLD ({},{},{})   ({},{},{})", ray.at(0).x, ray.at(0).y, ray.at(0).z, ray.at(1).x, ray.at(1).y, ray.at(1).z);
                bool result;
                glm::vec3 intersectionPoint;
                result = win->intersectionChecker(ray, intersectionPoint);
                if (result) {
                    //This is not correct TODO : FIXME 
                    m_vertices->at(0) =ray.direction.x;
                    m_vertices->at(1) =ray.direction.y;
                    m_vertices->at(2) =ray.direction.z;
                    SetColor(glm::vec4(FR_YELLOW));
                    redraw();
                }
                else {
                    SetColor(glm::vec4(FR_BROWN));
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