#include <navicube/fr_navicube.h>
#include <fr_window.h>
#include <fr_checkIntersection.h>
#include <navicube/fr_navicube_mesh.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
namespace FR {


	customShape::customShape(const std::string& fpath, glm::vec4 color, float silhouette) :Fr_Shape(fpath, color, silhouette) {
		 m_isClicked = false;
		}

	int  customShape::handle(int event) {
		//Detect if the widget is clicked
		Fr_Window *win = Fr_Window::getFr_Window();
		if (win != nullptr) {

			bool testMouseBound = m_boundBox->isRayInsideBoundingBox(win->getMouseEvents().MouseRay);
			m_isClicked = false;
			switch (event) {
			case FR_MOUSE_MOVE: {
				m_isMouseOver = testMouseBound;
			}break;
			case GLFW_MOUSE_LEFT_PUSH: {
				if (testMouseBound) {
					m_isClicked = true;
					return 1;
				}
			}break;
		  }
		}
		return 0;
	}
	bool customShape::isClicked(){
		return m_isClicked;
	}

	void customShape::Render(RenderInfo& info) {
		if (!m_active ||
			(info.render_transparent && m_color.a == 1) ||
			(!info.render_transparent && m_color.a < 1))
			return;
		Fr_Window* win = Fr_Window::getFr_Window();
		userData_ data;
		win->activeScene->getActiveCamera().getUserData(data);

		//Set up orthographic projection for fixed object
		float  m_OrthographicSize = 120.0f;
		float orthoLeft = -m_OrthographicSize * data.aspectRatio_ * 0.75f;
		float orthoRight = m_OrthographicSize * data.aspectRatio_ * 0.75f;
		float orthoBottom = -m_OrthographicSize * 0.5f;
		float orthoTop = m_OrthographicSize * 0.5f;

		 glm::mat4 proj= glm::ortho(orthoLeft,orthoRight,orthoBottom,orthoTop, -100.0f, 100.0f);
		 glm::mat4 viewMatrix = glm::mat4(1.0f);

		 glm::mat4 mvp =  viewMatrix;

		glm::vec3 pos = glm::vec3(140.f, 35.f, 0.f);
		viewMatrix = glm::translate(viewMatrix, pos);
		//glm::mat4 vie = glm::lookAt(pos, data.direction_, data.up_);
		mvp= proj * viewMatrix ;


		
		if (m_color.a == 1)
			Fr_Shape::RenderSilhouette(mvp);

		//Render texture also here.
		auto normalmatrix = glm::transpose(glm::inverse(info.modelview));
		m_shader->wdg_prog->Enable();
		m_Texture2D->Bind(0);
		LoadLights(m_shader->wdg_prog, info.lights);
		m_shader->wdg_prog->SetAttribLocation("position", 0);  //Position variable has (layout(location =0) inside objectshader_vs.glsl
		m_shader->wdg_prog->SetAttribLocation("texCoord", 1);  //Position variable has (layout(location =1 inside objectshader_vs.glsl
		m_shader->wdg_prog->SetAttribLocation("normal", 2);  //Position variable has (layout(location =1 inside objectshader_vs.glsl
		m_shader->wdg_prog->SetUniformMat4("modelview", info.modelview);
		m_shader->wdg_prog->SetUniformMat4("normalmatrix", normalmatrix);
		m_shader->wdg_prog->SetUniformMat4("mvp", mvp);
		m_shader->wdg_prog->SetUniformVec4("color", m_color);       //Object color - not light color
		m_shader->wdg_prog->SetUniformInteger("hasTexture", hasTexture());
		draw();      //You should make a draw call to get that  done
		m_Texture2D->Unbind();
		m_shader->wdg_prog->Disable();
		info.id++;
	}
	

	Fr_NavigationCube::Fr_NavigationCube():Fr_WGroup(NULL,NULL,"")
	{
		//We need to create all parts, they are 27 parts. 	
		for (int i = 0; i <meshDataPointers.size(); ++i) {
	
			std::shared_ptr<customShape> tempOBJ = std::make_shared<customShape>(*meshDataPointers[i]);
			
			//tempOBJ->NormalizeVertices();
			tempOBJ->m_Texture2D = std::make_shared<Fr_Texture2D>();
			std::string TexturePath = EXE_CURRENT_DIR + "/resources/Texture/";
			std::string imag = (TexturePath + "2.png");
			tempOBJ->hasTexture(0);
			if (tempOBJ->m_Texture2D->set2DTexture(imag))
			{
				tempOBJ->m_Texture2D->setup2DTexture();      //Don't forget to do this always
			}
			else {
				DEBUG_BREAK;
			}
			
			addWidget(tempOBJ);
		}
	}

	Fr_NavigationCube::~Fr_NavigationCube()
	{
	}

	int Fr_NavigationCube::handle(int event)
	{
		return 0;
	}


	void Fr_NavigationCube::Rotate(float x, float y, float z, float angle)
	{
	}

	void Fr_NavigationCube::Rotate(glm::vec3 axis, float angle)
	{
	}

	void Fr_NavigationCube::Translate(glm::vec3 v)
	{
	}

	void Fr_NavigationCube::Translate(float x, float y, float z)
	{
	}

	void Fr_NavigationCube::Scale(float x, float y, float z)
	{
	}

	void Fr_NavigationCube::Scale(glm::vec3 value)
	{
	}


}
