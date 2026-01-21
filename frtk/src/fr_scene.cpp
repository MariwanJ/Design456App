//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2026
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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include <fr_scene.h>
#include <fr_window.h>

#include <fr_log.h>

#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

#include <vector>

namespace FR {
	Fr_Scene::Fr_Scene() :m_cameras{}, m_active_camera(uint8_t(0)),
		m_Background{ 0.9f, 0.9f, 0.9f,1.0f },
		m_activeRay{ glm::vec3(0.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f) } {
	}

	void Fr_Scene::SetBackgroud(float r, float g, float b) {
		m_Background = glm::vec4(r, g, b, 1.0f);
	}
	void Fr_Scene::SetBackgroud(float r, float g, float b, float alfa) {
		m_Background = glm::vec4(r, g, b, alfa);
	}
	Fr_Camera& Fr_Scene::getActiveCamera(void) {
		return m_cameras[m_active_camera];
	}
	//TODO : THIS MUST BE FIXED !!!!!!
	void Fr_Scene::add3DObject(std::string fName)
	{
		if (fName.find(".off") != std::string::npos) {
			std::shared_ptr<Fr_Shape> newObj = std::make_shared<Fr_Shape>(fName);
			newObj->Translate(0, 0, 0);
			newObj->Scale(1, 1, 1);
			newObj->Rotate(0, 1, 0, 0); //TODO CHECK ME
			//texture
			newObj->m_Texture2D = std::make_shared<Fr_Texture2D>();
			std::string TexturePath = EXE_CURRENT_DIR + "/resources/Texture/";
			//std::string imag =(EXE_CURRENT_DIR+"../resources/Texture/test.png");
			//std::string imag = (TexturePath+"ts.png");
			std::string imag = (TexturePath + "2.png");
			//std::string imag = (TexturePath+"3.png");
			//std::string imag = (TexturePath+"default.png");

			if (newObj->m_Texture2D->set2DTexture(imag))
			{
				newObj->m_Texture2D->setup2DTexture();      //Don't forget to do this always
			}
			else {
				DEBUG_BREAK;
			}
			newObj->hasTexture(1);
			//convert fName to be a unique name
			std::string nFname = separateFN(fName);
			SceneItemStruct newtT(newObj, nFname);
			m_world.push_back(newtT);
			return;
		}
		else {
			DEBUG_BREAK;
			//Not implemented yet  - here .obj should be treated.
		}
		return;
	}

	void Fr_Scene::delete3DObject(SceneItemStruct& obj)
	{
		auto it = std::find(m_world.begin(), m_world.end(), obj);
		if (it != m_world.end()) {
			m_world.erase(it); // Erase the item if found
		}
		else {
			std::cout << "Item not found." << std::endl;
		}
	}

	void Fr_Scene::delete3DObject(std::shared_ptr<Fr_Widget> obj)
	{
		auto it = std::find_if(m_world.begin(), m_world.end(), [&](const SceneItemStruct& item) {
			return item.Sceneitem == obj;
			});
		if (it != m_world.end()) {
			m_world.erase(it); // Erase the item if found
		}
		else {
			std::cout << "Item not found." << std::endl;
		}
	}

	void Fr_Scene::setBackgroud(float r, float g, float b, float alfa) {
		m_Background = glm::vec4(r, g, b, alfa);
	}

	void Fr_Scene::setBackgroud(glm::vec4 color) {
		m_Background = color;
	}

	/**
	 * Setup active camera by taking the name .
	 * It will activate the camera and update the view matrix
	 * \param name  Reference to a string which is the name of the camera Perspective,Orthographic, Top, Bottom, ..etc
	 * \return a reference to the active camera
	 */
	void Fr_Scene::setupActiveCamera(const char* name, RenderInfo& info) {
		uint8_t cam = getCameraIndex(name);
		setupActiveCamera(cam, info);
	}

	void Fr_Scene::setupActiveCamera(uint8_t  val, RenderInfo& info)
	{
		m_cameras[val].isActive(true);
		m_cameras[val].SetupCamera(info.projection, info.modelview);
		info.screenDim = Fr_Window::getScreenDim();
	}

	void Fr_Scene::CreateDefaultCameras(void)
	{
		for (int i = 0; i < TOTAL_CAMS; i++) {
			m_cameras[i].setType(uint8_t(i));
			m_cameras[i].setupCameraHomeValues();
			switch (i) {
			case 0: {
				/*Normal view PERSPECTIVE, HOME
						position 17.463835 -17.463825 13.463827\n
						orientation 0.74290609 0.30772209 0.59447283  1.2171158\n
						nearDistance 0.42925534\n
						farDistance 1761.75\n
						aspectRatio 1\n
						focalDistance 30.248238\n
						heightAngle 0.78539819\n\n}\n'
				*/
				m_cameras[i].Rotate(glm::vec3(0.7429f, 0.307f, 0.594f), -69.7f);
			}break;
			case 1: {
				//ORTHOGRAPHIC

				m_cameras[i].Rotate(glm::vec3(0.74290609f, 0.30772209f, 0.59447283f), 69.7f);
			}break;
			case 2: {
				/*TOP
				 position 15.337841 10.960548 102.60384\n
				 orientation 0 0 1  0\n
				 nearDistance 102.50124\n
				 farDistance 102.70644\n
				 aspectRatio 1\n
				 focalDistance 100\n
				 height 44.932899\n\n}\n'
				*/
				m_cameras[i].Rotate(glm::vec3(0.0f, 0.0, 1.0f), 0);
			}break;
			case 3: {
				/*Bottom
				 position 10.531155 7.5401545 -97.396126\n
				 orientation -0.99999994 1.4210855e-014 9.4830476e-008  3.1415935\n
				 nearDistance 97.298668\n
				 farDistance 97.493576\n
				 aspectRatio 1\n
				 focalDistance 100\n
				 height 44.932903\n\n}\n'
				*/
				m_cameras[i].Rotate(glm::vec3(-1.0f, 0.0f, 0.0f), 180);
			}break;
			case 4: {
				/**
				 *  FRONT
				  position 28.817665 -89.039444 2.6038942\n
				  orientation -1 4.214686e-007 8.4293717e-008  4.7123895\n
				  nearDistance 34.005363\n
				  farDistance 144.1835\n
				  aspectRatio 1\n
				  focalDistance 100\n
				  height 44.932899\n\n}\n'
						 *
				 */
				m_cameras[i].Rotate(glm::vec3(-1.0f, 0, 0), 270.0f);
			}break;
			case 5: {
				/*REAR
					position 15.337867 110.96054 2.6038241\n
					orientation 1.4901161e-008 - 0.70710683 - 0.70710671  3.141593\n
					nearDistance 55.904575\n
					farDistance 166.1265\n
					aspectRatio 1\n
					focalDistance 100\n
					height 44.932899\n\n}\n'
					*/
				m_cameras[i].Rotate(glm::vec3(0.f, -0.70710683, -0.70710671f), 270.0f);
			}break;
			case 6: {
				/*
				RIGHT
					position 115.33784 10.960509 2.6038659\n
					orientation - 0.57735032 - 0.57735026 - 0.5773502  4.1887908\n
					nearDistance 60.277466\n
					farDistance 170.50819\n
					aspectRatio 1\n
					focalDistance 100\n
					height 44.932899\n\n
					*/
				m_cameras[i].Rotate(glm::vec3(-0.577f, -0.577f, -0.577f), 240.f);
			}break;

			case 7: {
				/*LEFT
					position - 71.182274 10.960546 2.6038406\n
					orientation 0.57735014 - 0.5773505 - 0.5773502  2.0943947\n
					nearDistance 16.166088\n
					farDistance 126.30847\n
					aspectRatio 1\n
					focalDistance 100\n
					height 44.932899\n\n}\n'
					*/
				m_cameras[i].Rotate(glm::vec3(0.57f, -0.57f, -0.57f), 270.0f);
			}break;
			}
		}
	}

	SceneItemStruct Fr_Scene::CreateDefaultSunLight(void)
	{   //TODO : how many sun we should have???
		std::shared_ptr<Fr_Light> sun = std::shared_ptr<Fr_Light>(new Fr_Light);
		sun->SetPosition(0.0f, 0.0f, 1000.0f); // Position is fine for a sun-like light
		sun->SetDiffuse(0.50f, 0.50f, 0.50f); // Higher diffuse value for sunlight
		sun->SetAmbient(0.5f, 0.5f, 0.5f); // Ambient value can remain as is
		sun->EnableShadowMap(glm::vec3(0, 0, 1),
			glm::vec3(0, 0, 4),
			glm::ortho<float>(-10, 10, -10, 10, 1, 100));

		sun->isActive(true);
		SceneItemStruct sunItem(sun, "Sun");
		m_world.push_back(sunItem);
		return sunItem;
	}

	SceneItemStruct  Fr_Scene::CreateGrid() {
		auto gr = std::shared_ptr<Fr_Grid>(new Fr_Grid);
		SceneItemStruct gridsItem(gr, "Grid");
		gr->CreateGrid();
		m_world.push_back(gridsItem);
		return gridsItem;
	}

	SceneItemStruct  Fr_Scene::CreateAxis() {
		auto ax = std::shared_ptr<Fr_Axis3D>(new Fr_Axis3D);
		SceneItemStruct   allAxis(ax, "Axis3D");
		ax->CreateAxis3D();
		m_world.push_back(allAxis);
		return allAxis;
	}

	void Fr_Scene::setupScene() {
		CreateDefaultCameras();
		CreateDefaultSunLight();
		CreateAxis();
		CreateGrid();
	}
	int Fr_Scene::findClosestMeshToRay(const ray_t& m_activeRay) {
		Fr_Window* win = Fr_Window::getFr_Window();
		assert(win != 0);
		GLFWwindow* glfWin = Fr_Window::getCurrentGLWindow();
		glm::vec3 intersectionPoint(0.0f, 0.0f, 0.0f);
		float closestT = std::numeric_limits<float>::max();
		float t;
		int IndexOfclosestItem = -1;
		for (size_t i = 0; i < m_world.size(); ++i) {
			if (intersectRayOpenMesh(m_activeRay, m_world[i].Sceneitem->m_mesh, intersectionPoint)) {
				t = glm::length(intersectionPoint - m_activeRay.position);
				if (t < closestT) {
					closestT = t;
					IndexOfclosestItem = i;
				}
			}
		}
		return IndexOfclosestItem;
	}

	void Fr_Scene::setRayValue(ray_t val)
	{
		m_activeRay = val;
	}

	/**
	 * Scene Render. Main function to draw all objects inside the Scene
	 *
	 */

	ray_t Fr_Scene::getRayValue(void) const
	{
		return m_activeRay;
	}

	void Fr_Scene::RenderScene() {
		Fr_Window* win = Fr_Window::getFr_Window();
		assert(win != 0);

		ImGuiWindowFlags window_flags = 0 | ImGuiWindowFlags_NoTitleBar;
		/*        FR_PROFILE_FUNCTION();
				FR_PROFILE_SCOPE("imgui_ViewPort");   */
		int windowX, windowY;
		GLFWwindow* window = glfwGetCurrentContext();
		glfwGetWindowPos(window, &windowX, &windowY);

		// Camera setup
		RenderInfo render_info;
		setupActiveCamera(m_active_camera, render_info);
		render_info.modelview = m_cameras[m_active_camera].GetViewMatrix();
		render_info.projection = m_cameras[m_active_camera].getProjection();

		// Light setup
		std::string_view str = "Sun";
		std::shared_ptr<Fr_Light> sunItem;
		findItemByName(sunItem, str);
		if (sunItem) {
			sunItem->SetupLight(render_info.modelview, render_info.lights);
		}
		// Render all objects
		render_info.id = 0;
		render_info.render_transparent = false;

		glViewport(0, 0, win->w(), win->h());
		// Enable depth testing
		glCheckFunc(glEnable(GL_DEPTH_TEST));
		glClearColor(win->clear_color.x * win->clear_color.w,
			win->clear_color.y * win->clear_color.w,
			win->clear_color.z * win->clear_color.w,
			win->clear_color.w);
		glCheckFunc(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		glEnable(GL_LINE_SMOOTH);

		// glCheckFunc(glDepthFunc(GL_LESS));
		RenderPrimativeShapes(render_info);
		// Render 3D objects
		Render(render_info);
		//// Render transparent items
		RenderText(render_info);

		render_info.render_transparent = true;
		Render(render_info);
	}

	bool Fr_Scene::deleteItemByID(std::string_view str) {
		auto it = std::remove_if(m_world.begin(), m_world.end(),
			[str](const SceneItemStruct& obj) { return obj.name == str; });
		if (it != m_world.end()) {
			m_world.erase(it, m_world.end());
			return true;
		}
		return false;
	}

	bool Fr_Scene::replaceItemByID(int id, SceneItemStruct& newItem) {
		auto it = std::find_if(m_world.begin(), m_world.end(),
			[id](const SceneItemStruct& obj) { return obj.id == id; });
		if (it != m_world.end()) {
			*it = std::move(newItem);
			return true;
		}
		return false;
	}

	// Item management functions
	void Fr_Scene::addObject(SceneItemStruct&& item) {
		m_world.push_back(std::move(item));
	}

	void Fr_Scene::addObject(std::shared_ptr<Fr_Widget> item, std::string name)
	{
		SceneItemStruct nItem(item, name);
		m_world.push_back(std::move(item));
	}

	// Delete a SceneItemStruct by its unique identifier
	bool Fr_Scene::deleteItemByID(int id) {
		auto it = std::remove_if(m_world.begin(), m_world.end(),
			[id](const SceneItemStruct& obj) { return obj.id == id; });

		if (it != m_world.end()) {
			m_world.erase(it, m_world.end());
			return true;
		}
		return false;
	}

	void Fr_Scene::Render(FR::RenderInfo& info) {
		for (size_t i = 0; i < m_world.size(); ++i) {
			m_world[i].Sceneitem->Render(info);
		}
		RenderText(info);
	}
	void Fr_Scene::RenderText(FR::RenderInfo& info) {
		for (size_t i = 0; i < m_world.size(); ++i) {
			if (m_world[i].Sceneitem->m_label) {
				if (m_world[i].Sceneitem->m_label->lbl_visible())
					m_world[i].Sceneitem->RenderText(info);
			}
		}
	}

	void Fr_Scene::RenderPrimativeShapes(FR::RenderInfo& info) {
		// Iterate over entities with Fr_Grid and ItemName components
		std::vector<std::shared_ptr<Fr_Grid>> grid;
		findOccurrencesOfType(grid, NODETYPE::FR_GRID);

		for (int i = 0; i < grid.size(); i++) {
			grid[i]->getGridShader()->Render(info);
		}
		std::shared_ptr<Fr_Axis3D>  axis;
		findItemByName(axis, "Axis3D");

		auto blue = axis->getBlue();
		auto green = axis->getGreen();
		auto red = axis->getRed();
		auto zblue = axis->getZBlue();

		blue->Render(info);
		green->Render(info);
		red->Render(info);
		zblue->Render(info);
	}

	void Fr_Scene::RenderSilhouette(const glm::mat4& mvp) {
	}

	/**  ---------------------------------- */

	// Function to calculate the normal of a triangle defined by three vertices
	glm::vec3 calculateNormal(const glm::vec3& V0, const glm::vec3& V1, const glm::vec3& V2) {
		glm::vec3 edge1 = V1 - V0;
		glm::vec3 edge2 = V2 - V0;
		return glm::normalize(glm::cross(edge1, edge2));
	}

	// Function to test ray intersection against a set of vertices forming triangles
	void testRayAgainstVertices(const glm::vec3& rayOrigin, const glm::vec3& rayDirection, const std::vector<glm::vec3>& vertices) {
		glm::vec3 intersectionPoint;

		if (vertices.size() < 3) return;

		// Iterate over triangles formed by vertices
		for (size_t i = 0; i < vertices.size(); i += 3) {
			if (i + 2 >= vertices.size()) break; // Ensure we have enough vertices

			// Get the triangle vertices
			glm::vec3 V0 = vertices[i];
			glm::vec3 V1 = vertices[i + 1];
			glm::vec3 V2 = vertices[i + 2];

			// Calculate the normal of the triangle
			glm::vec3 normal = calculateNormal(V0, V1, V2);

			// Calculate the plane constant using one of the triangle vertices
			float planeConstant = -glm::dot(normal, V0);

			// Check for intersection struct
			//                 glm::intersectRayPlane(const genType &orig, const genType &dir, const genType & planeOrig, const genType &planeNormal, genType::value_type &intersectionDistance)
			bool intersects = glm::intersectRayPlane(rayOrigin, rayDirection, normal, intersectionPoint, planeConstant);
			if (intersects) {
				std::cout << "Intersection with triangle at point: ("
					<< intersectionPoint.x << ", "
					<< intersectionPoint.y << ", "
					<< intersectionPoint.z << ")" << std::endl;
			}
		}
	}

	/** ------------------------------------ */

	auto Fr_Scene::SearchIntersection(const glm::vec3& ray)
	{
		for (auto node : m_world) {
		}
	}

	// Returns the unique name generated
	std::string Fr_Scene::getUniqueName(const std::string& name, const std::vector<std::string>& names)
	{
		std::string result;
		// Find the indices of elements that start with the specified prefix
		auto it = std::find_if(names.begin(), names.end(), [name](const std::string& s) { return s.find(name) == 0; });
		// Output the indices
		if (it != names.end()) {
			//found
			std::string letters, numbers;
			// Use a lambda function to separate letters and numbers
			std::for_each(name.rbegin(), name.rend(), [&letters, &numbers](char ch) {
				if (std::isalpha(ch)) {
					// If it's a letter, add it to the letters string
					letters = ch + letters;
				}
				else if (std::isdigit(ch)) {
					// If it's a digit, add it to the numbers string
					numbers = ch + numbers;
				}
				else {
					// Break the loop if a non-alphanumeric character is encountered
					return;
				}
				});
			if (numbers.size() == 0) {
				numbers = "001";
				result = letters + numbers;
			}
			else {
				result = letters + std::to_string((atoi(numbers.c_str()) + 1));
			}
		}
		else {
			std::string result = name;
		}
		return result;
	}

	//MOUSE PICKER PART - TO AVOID Include problem we put this part here.
	bool Fr_Window::intersectionChecker(const ray_t& ray, glm::vec3& intersectionPoint) {
		{
			//TODO FIXME :
			for (int j = 0; j < activeScene->m_world.size(); j++) {
				switch (activeScene->m_world.at(j).Sceneitem->type()) {
				case NODETYPE::FR_LINE_WIDGET: {
					std::shared_ptr<std::vector<float>> vert = activeScene->m_world.at(j).Sceneitem->getVertices();
					std::vector<glm::vec3> ln;
					for (int ii = 0; ii < int(vert->size()); ii += 3) {
						ln.push_back(glm::vec3(vert->at(ii), vert->at(ii + 1), vert->at(ii + 2)));
					}
					glm::vec3 intersectionPoint(0.0f);
					float t;
					if (intersectLineSegment3D(ray, ln, intersectionPoint, t)) {
						// Check if the intersection point is within the bounds of the line segment plus radius
						glm::vec3 minPoint = glm::min(ln[0], ln[1]);
						glm::vec3 maxPoint = glm::max(ln[0], ln[1]);
						for (const auto& vertex : ln) {
							minPoint = glm::min(minPoint, vertex);
							maxPoint = glm::max(maxPoint, vertex);
						}
						// Expand bounds by the radius
						minPoint -= glm::vec3(m_MousePickerRadius);
						maxPoint += glm::vec3(m_MousePickerRadius);

						if (intersectionPoint.x >= minPoint.x && intersectionPoint.x <= maxPoint.x &&
							intersectionPoint.y >= minPoint.y && intersectionPoint.y <= maxPoint.y &&
							intersectionPoint.z >= minPoint.z && intersectionPoint.z <= maxPoint.z) {
							FRTK_CORE_INFO("LINE - found found");
							return true;
						}
						else {
							FRTK_CORE_INFO("intersection point is outside the line segment with radius");
						}
					}
					else
					{
						//not found
						;
					}
				}; break;
				case  NODETYPE::FR_FACE_WIDGET: {
					std::shared_ptr<std::vector<float>> vert = activeScene->m_world.at(j).Sceneitem->getVertices();
					std::vector<glm::vec3> fc;
					for (int ii = 0; ii<int(vert->size()); ii += 3)
						fc.push_back(glm::vec3(vert->at(ii), vert->at(ii + 1), vert->at(ii + 2)));
					glm::vec3 intersectionPoint;
					float t;
					if (intersectRayTriangle(ray, fc, intersectionPoint, t)) {
						return true;
					}
					else
						;
				} break;
				case  NODETYPE::FR_SHAPE:
				case  NODETYPE::FR_MESH:
					//return node->m_boundBox->isRayInsideBoundingBox(ray);
					break;
				}
			}
			return false;
		}
	}

	int Fr_Scene::handle(int ev)
	{
		int res = handle_selection(ev);
		/*
		if (res == 1) return 1;
		else if (res == -1) return 0;
		*/
		if (res)
			FRTK_CORE_INFO("res is found");
		//TODO: Should we, even if the mouse was a selection action, send the event to the objects??
		for (auto& obj : m_world) {
			obj.Sceneitem->handle(ev);
		}

		return 0; //We could not use the event .. Return 0 as we don't care , Never return value >0 if you don't care
	}

	bool Fr_Scene::pickAFace( size_t IndexOfclosestItem, OpenMesh::FaceHandle& pickedFace, float& outT)
	{
		float closestT = std::numeric_limits<float>::max();
		bool found = false;

		auto& mesh = m_world[IndexOfclosestItem].Sceneitem->m_mesh;

		for (const auto& face : mesh.faces())
		{
			std::vector<glm::vec3> verts;
			verts.reserve(4);

			for (auto fv = mesh.fv_iter(face); fv.is_valid(); ++fv)
			{
				const auto& p = mesh.point(*fv);
				verts.emplace_back(p[0], p[1], p[2]);
			}

			if (verts.size() < 3)
				continue;

			const glm::vec3& v0 = verts[0];

			for (size_t i = 1; i + 1 < verts.size(); ++i)
			{
				std::vector<glm::vec3> tri = {
					v0, verts[i], verts[i + 1]
				};

				float t;
				glm::vec3 hit;

				if (intersectRayTriangle(m_activeRay, tri, hit, t))
				{
					if (t > 0.0f && t < closestT)
					{
						closestT = t;
						pickedFace = face;
						found = true;
					}
				}
			}
		}

		if (!found)
			return false;

		outT = closestT;
		return true;
	}


	int Fr_Scene::handle_selection(int ev) {
		//We need to find closest object to the screen,
		// if the object is behind another object, we should ignore it
		Fr_Widget* closestItem = nullptr;
		float t = 0.0f;

		glm::vec3 intersectionPoint;

		struct MeshItem { MeshHandle handle; Fr_Widget  widget; };
		struct FaceItem { FaceHandle handle; Fr_Widget  widget; };
		struct EdgeItem { EdgeHandle handle; Fr_Widget  widget; };
		struct VertexItem { VertexHandle handle; Fr_Widget  widget; };

		std::vector<MeshItem>   sel_mesh;
		std::vector<FaceItem>   sel_face;
		std::vector<EdgeItem>   sel_edge;
		std::vector<VertexItem> sel_vert;

		Fr_Window* win = Fr_Window::getFr_Window();
		assert(win != 0);
		GLFWwindow* glfWin = Fr_Window::getCurrentGLWindow();

		eventData_t glfData = win->GLFWevents();
		bool ctrlPressed = (glfData.lastMod & GLFW_MOD_CONTROL);
		bool mouseClicked = (ev == FR_LEFT_PUSH);
		int result = -1;
		int IndexOfclosestItem = 0;
		//Here, we should try to send the events to each object in the scene.
		// Depending on where the events occur, object should get them otherwise just ignore them
		if (mouseClicked) {
			IndexOfclosestItem = findClosestMeshToRay(m_activeRay);

			if (IndexOfclosestItem < 0) {
				//Ray did not hit anything
				for (size_t i = 0; i < m_world.size(); ++i) {
					m_world.at(i).Sceneitem->m_mesh.clearAllSelections(); //Deselect all objects that are not visible
				}
				result = -1; //no selection, all cleared
			}
			else {
				if (!ctrlPressed) {
					m_world.at(IndexOfclosestItem).Sceneitem->m_mesh.clearAllSelections();
				}
				if (m_world.at(IndexOfclosestItem).Sceneitem->m_boundBox->isRayInsideBoundingBox(m_activeRay)) {
					switch (m_currentSelMode) {
					case SelectionMode::Mesh: {
						m_world.at(IndexOfclosestItem).Sceneitem->m_mesh.selectMesh(true);
						return 1;
					} break;
					case SelectionMode::Face:
					{
						OpenMesh::FaceHandle pickedFace;
						float t;
						if (pickAFace(IndexOfclosestItem, pickedFace, t)) {
							if (pickedFace.is_valid())
							{
								selectCoplanarFaces(m_world.at(IndexOfclosestItem).Sceneitem->m_mesh, pickedFace);
							}
						}
					}
					break;

					case SelectionMode::Edge:
					{
						OpenMesh::FaceHandle pickedFace;
						float faceT;

						if (!pickAFace(IndexOfclosestItem, pickedFace, faceT))
							break;
						float closestS = FLT_MAX;
						OpenMesh::EdgeHandle bestEdge;
						bool found = false;

						constexpr float depthEpsilon = 1e-3f;

						for (auto fh : m_world[IndexOfclosestItem].Sceneitem->m_mesh.fh_range(pickedFace))
						{
							OpenMesh::EdgeHandle eh = m_world[IndexOfclosestItem].Sceneitem->m_mesh.edge_handle(fh);

							// Get edge endpoints
							OpenMesh::HalfedgeHandle heh = m_world[IndexOfclosestItem].Sceneitem->m_mesh.halfedge_handle(eh, 0);
							OpenMesh::VertexHandle v0 = m_world[IndexOfclosestItem].Sceneitem->m_mesh.from_vertex_handle(heh);
							OpenMesh::VertexHandle v1 = m_world[IndexOfclosestItem].Sceneitem->m_mesh.to_vertex_handle(heh);

							const auto& p0 = m_world[IndexOfclosestItem].Sceneitem->m_mesh.point(v0);
							const auto& p1 = m_world[IndexOfclosestItem].Sceneitem->m_mesh.point(v1);

							std::vector<glm::vec3> vert = { glm::vec3(p0[0], p0[1], p0[2]),glm::vec3(p1[0], p1[1], p1[2]) };

							glm::vec3 hitPoint;
							float s;

							if (intersectLineSegment3D(m_activeRay, vert, hitPoint, s))
							{
								if (s < closestS)
								{
									closestS = s;
									bestEdge = eh;
									intersectionPoint = hitPoint;
									found = true;
								}
							}
						}

						if (found)
						{
							m_world[IndexOfclosestItem].Sceneitem->m_mesh.selectEdge(bestEdge, true);
							result = 1;
						}
					}
					break;

					case SelectionMode::Vertex: {
						auto& mesh = m_world[IndexOfclosestItem].Sceneitem->m_mesh;

						for (auto v_it = mesh.vertices_begin(); v_it != mesh.vertices_end(); ++v_it)
						{
							OpenMesh::VertexHandle vh = *v_it;
							const auto& p = mesh.point(vh);
							glm::vec3 vertexPos(p[0], p[1], p[2]);
							if (intersectPointIn3D(m_activeRay, vertexPos))
							{
								mesh.selectVertex(vh, true);
								result = 1; // done, only one vertex per click
								break;
							}
						}
					} break;
					default: {} break;
					}
				}
				else
				{
					//might be multi selection since the ray was not inside the boundbox of the current object
					if (!ctrlPressed) {
						for (size_t i = 0; i < m_world.size(); ++i) {
							m_world.at(i).Sceneitem->m_mesh.clearAllSelections(); //Deselect all objects that are not visible
						}
						result = -1; //no selection, all cleared
					}
					else
					{
						//Multi - Selection.
					}
				}
				result = -1;
			}
		}
		if (result == 1) {
			m_world[IndexOfclosestItem].Sceneitem->initializeVBO(); //re-create all vertices
			return 1;
		}
		return 0;
	}
}