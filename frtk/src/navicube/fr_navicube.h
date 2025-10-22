#ifndef FR_NAVICUBE_H
#define FR_NAVICUBE_H

#include <fr_wgroup.h>
#include <halfedge/fr_shape.h>

namespace FR {

	class customShape : public Fr_Shape {
	public :
		customShape(const std::string& fpath, glm::vec4 color=glm::vec4(FR_LIGHTGRAY), float silhouette=0.01);
		int handle(int event);
		bool isClicked();
	private: 
		bool m_isMouseOver;
		bool m_isClicked;
	};

	class Fr_NavigationCube : public Fr_WGroup {
	public:
		Fr_NavigationCube(); 
		~Fr_NavigationCube();

		int handle(int event)override;
		/** Multiply the current matrix by a rotation matrix */
		void Rotate(float x, float y, float z, float angle) override;
		void Rotate(glm::vec3 axis, float angle) override;

		/** Translate the widget to the new location */
		void Translate(glm::vec3 v) override;
		void Translate(float x, float y, float z) override;

		/** Scale the object by a percentage */
		void Scale(float x, float y, float z) override;
		void Scale(glm::vec3 value) override;

	};

}



#endif //FR_NAVICUBE_H

