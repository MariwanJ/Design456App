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
#ifndef FR_WIDGET_H
#define FR_WIDGET_H

#include <fr_constants.h>
#include <stdexcept>
#include <fr_shader_program.h>
#include <fr_core.h>
#include <fr_boundbox.h>
#include <fr_texture2d.h>
#include <fr_transform.h>

#include<fr_genID.h>

//Introducing OpenMesh to Widget System also
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>

namespace FR {
    /**
  * Holds the light information
  */
    struct LightInfo {
        glm::vec4 lightcolor;
        glm::vec4 position;
        glm::vec4 diffuse;
        glm::vec4 specular;
        glm::vec4 ambient;
        glm::vec3 attenuation;
        bool is_spot;
        glm::vec3 direction;
        float cutoff;
        float exponent;
    };

    /**
     * Holds the render information
     */
    struct RenderInfo {
        int id;
        glm::mat4 modelview;
        glm::mat4 projection;
        std::vector<LightInfo> lights;
        //ShadowMapInfo shadowmap;
        bool render_transparent;
        screenDim_t screenDim;
    };

    const size_t kMaxLights = 8;        //This is important to consider. This is also defined in the   objectshader_fs.glsl as MAX_LIGHTS

    typedef struct {
        //TODO : FIXME: This is just a dummy construction. this should be changed later
        union {
            std::string str;
            int val;
        };
    } userWidgetData;


    typedef struct {
        glm::vec3 offset;        // Position relative to the widget,TODO: SHOULD BE RELATIVE OR ABS
        std::string text;
        std::shared_ptr<std::string> fnFont; // freetype Font used for rendering, filepath
        glm::vec4 color;
        bool visible;              // Visibility flag
        uint8_t type;               //ORTHO - PERSPECTIVE 
        size_t pixelSize;
        float scale;
    }label_t;



    //diff shader program
    typedef struct {
        std::shared_ptr <ShaderProgram> wdg_prog;        //for the widget itself
        std::shared_ptr <ShaderProgram> widgPoits_prog; //for points
        std::shared_ptr <ShaderProgram> silhouette_prog; // Dark shape and outline of object
        std::shared_ptr <ShaderProgram> texture_prog;
        std::shared_ptr <ShaderProgram> txtFont_program;
    }Shader_t;

    class NotImplementedException : public std::logic_error
    {
    public:
        NotImplementedException() : std::logic_error{ "not implemented." } {}
    };

    class Fr_Widget;
    class Fr_Group;
    class Shape;
    class Fr_TwoD_Drawing;

    /** Default callback type definition for all frtk widgets */
    typedef void (Fr_Callback)(Fr_Widget*, void*);

    /** Default callback type pointer definition for all frtk widgets */
    typedef Fr_Callback* Fr_Callback_p;

    class FRTK_API Fr_Widget {
        /** Abstract Base class used to create all Widget.
            You need to subclass this object
            to be able to create any widget,
            and you should always have a Fr_Group
            widget which acts like a container for the widgets.
        */

    public:
        friend class Fl_Group;
 

        // Default constructor is disallowed
        Fr_Widget() = delete;
        Fr_Widget(std::shared_ptr <std::vector<float>> verticies,
            std::shared_ptr <std::vector<unsigned int>> indicies,
            std::string label);

        virtual void init(void); //We need this if the widget is created (subclassed) without verticies, like in reading files.

        /** Virtual destructor */
        virtual ~Fr_Widget();

        /** Create shader program that will be used by the entire widget system */
        virtual void CreateShader();

        /** Sets the lights
            Returns the light info by reference
        */
        virtual void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights);

        /** Renders the node */
        virtual void Render(RenderInfo& info);

        /** Renders Vertexes in orthographic projection separate from normal rendering */
        virtual void RenderVertexes(RenderInfo& info);

        /** Renders Text (Freetype Font)*/
        virtual void RenderText(RenderInfo& info);
        
        virtual bool SetupTexture2D();
        virtual void RenderTexture2D();

        NODETYPE type();
        twodType_t lineType(void);
        void lineType(twodType_t ltype);
        void type(NODETYPE newVal);
        bool isOfType(const NODETYPE& newVal);

        /** Sets whether the node is active */
        void isActive(bool active);
        bool isActive(void);

        void SetNormalizeMesh(bool value);
        bool getNormalizeMesh();

        /** Main draw function */
        virtual void draw();

        virtual void draw_2d();

        /** Redraw the last object */
        virtual void redraw();

        /** Label draw function */

        virtual void lbl_redraw();

        /** Initializes VBO and other stuff */
        virtual bool setup();

        /** Sets the label */
        void label(std::string& lbl);

        void lbl_visible(bool v);
        bool lbl_visible();

        void lblType(uint8_t lbltype);
        const uint8_t lblType(void);

        std::string label() const;

        /** Sets the font */
        void font(std::string& forntName);
        std::shared_ptr<std::string> font() const;

        /** Sets the font size */
        void fontSize(int size_);

        void fontColor(glm::vec4 col);

        void fontColor(float r, float g, float b, float a);

        void lblOffset(glm::vec3 nval);

        /** Resizes the widget */
        virtual void resize(std::shared_ptr<std::vector<float>> verticies,
            std::shared_ptr<std::vector<unsigned int>> indicies);

        bool Resizable();
        bool active();
        void activate(bool value);
        bool has_focus();
        void has_focus(bool value);
        void visible(bool value);
        bool visible(void);

        /** Handle events - must be subclassed */
        virtual int handle(int e);

        /** Let the object be visible */
        virtual void show();

        /** Hide the object */
        virtual void hide();

        /** Gets the current callback function for the widget */
        Fr_Callback_p callback() const;

        /** From shader */
        virtual void WidgetShader(glm::vec4 color = glm::vec4(FR_WHITE), float silhouette = 0.005);

        /** Sets the color */
        void SetColor(glm::vec4 c);

        /** Sets the opacity */
        void SetOpacity(float alpha);
        virtual GLuint getCurrentTexturer(void);

        /** Retrieve tab index of the widget */
        virtual int tabIndex(void) const;

        /** Set Tab index of the widget */
        void tabIndex(int index);

        /** Define if the widget has texture */
        void hasTexture(int val);
        int hasTexture(void);

        /** Multiply the current matrix by a rotation matrix */
        virtual void Rotate(float x, float y, float z, float angle);
        virtual void Rotate(glm::vec3 axis, float angle);

        /** Translate the widget to the new location */
        virtual void Translate(glm::vec3 v);
        virtual void Translate(float x, float y, float z);

        /** Scale the object by a percentage */
        virtual void Scale(float x, float y, float z);
        virtual void Scale(glm::vec3 value);

        /** Get widget matrix */
        glm::mat4 GetMatrix(void);

        /** Get inverse of the matrix */
        glm::mat4 GetInvers(void);

        /** Normalize vertices */
        void NormalizeVertices();

        /** Calculate normals */
        void CalculateNormals();

        /** Get a vertex (x,y,z) from the vertices at index 'index' */
        glm::vec3 GetVertex(unsigned int ind, const float vertices[]);
        glm::vec3 GetVertex(unsigned int ind);

        /** Method to retrieve a shared pointer to the vector of vertices */
        virtual std::shared_ptr<std::vector<float>> getVertices(void);

        /** Set vertex at an index */
        void SetVertex(unsigned int ind, const glm::vec3& vertex);

        virtual void calcualteTextCoor(int width, int height);


        //
        virtual int initializeVBO();
        virtual void DrawPoints();
   
        void pointSize(uint8_t val);
        uint8_t pointSize();
        void lineWidth(uint8_t wid);
        uint8_t lineWidth();



        /** Return row pointer - must be overridden in the children */
        // virtual auto getPointer() -> std::shared_ptr<Fr_Widget>;

        void Parent(int index);

        /** BoundBox for all objects */
        std::shared_ptr<cBoundBox3D> m_boundBox;
 
    protected:
        
        virtual void lbl_draw();

        virtual void do_callback();
        virtual void calculateTextCoor(); //might needs to be overridden

        void CalculateTrianglesNormals();

        std::shared_ptr<std::vector<float>> m_vertices;
        std::shared_ptr<std::vector<uint8_t>> m_selected;
        std::vector<float> m_textcoord; // Texture Coordinates
        std::shared_ptr<std::vector<unsigned int>> m_indices; // We don't use glm::vec3 but we can even so use it for Triangle drawing. Decide that by the drawing type.
        std::shared_ptr<std::vector<float>> m_vertCoord; // must be calculated internally
        std::shared_ptr<std::vector<float>> m_normals;
        std::shared_ptr<std::vector<glm::vec3>> m_triangles_normals; //triangles normals
        std::shared_ptr<std::vector<float>> m_textCoord;
        
        std::shared_ptr<Shader_t> m_shader; // Program for shared resources, cannot be static

        bool m_active;
        int uniqueIndex;
        int m_Parent; // -1 for Abstract class that doesn't have parent, and for the Root class

        // OpenMesh Mesh. This must be defined here
        MyMesh m_mesh;

        // OpenMesh Edges object. In this widget system we use edges not faces.
        // We can make mesh of it but it is 2D so we have only edges .. not faces TODO: IS THIS CORRECT???? 2024-12-14
        std::vector<std::pair<MyMesh::VertexHandle, MyMesh::VertexHandle>> openEdges;

        /** From shader */
        /** Sets the uniform light data */
        virtual void LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights);

        Fr_Callback* m_callback_;

        label_t m_label;

        bool m_visible;
        bool m_focus;
        bool m_resizable;
        int m_tabIndex;
        int m_hasTexture;
        glm::mat4 m_Matrix;
        bool m_normalized; //if the verticies are normalized

        // Attributes
        glm::vec4 m_color;
        float m_silhouette;
        GLuint m_texture; // Used to return the texture for imgui rendering inside window.
        NODETYPE m_WidgType;
        twodType_t m_lineType;

        unsigned int m_vbo[NUM_OF_VBO_BUFFERS]; 
        unsigned int m_vao;
        unsigned int m_vao_points;
        unsigned int m_vao_txt;
        unsigned int m_lineWidth;
        unsigned int m_pointSize;


    };



}
#endif