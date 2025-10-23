#include <navicube/fr_navicube.h>
#include <fr_window.h>
#include <fr_checkIntersection.h>
#include <navicube/fr_navicube_mesh.h>
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
	

	Fr_NavigationCube::Fr_NavigationCube():Fr_WGroup(NULL,NULL,"")
	{
		//We need to create all parts, they are 27 parts. 
		for (int i = 0; i <meshDataPointers.size(); ++i) {
	
			std::shared_ptr<customShape> tempOBJ = std::make_shared<customShape>(*meshDataPointers[i]);
			
			
			tempOBJ->ConvertVerticesNormalized();
			
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
