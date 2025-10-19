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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_SCENE_H
#define FR_SCENE_H

#include<fr_core.h>

#include <fr_transform.h>
#include <fr_light.h>
#include <fr_camera.h>
#include <fr_genID.h>
#include <sceneItem/fr_sceneItem.h>
#include <grid/fr_primatives.h>
#include <grid/fr_grid_shader.h>
#include <grid/fr_grid.h>
#include <grid/fr_axis3D.h>



namespace FR {
	class FRTK_API Fr_Scene {
	public:
		friend Fr_Window;
		/**
		 * Default Constructor
		 */
		Fr_Scene();
		/**
		 * Sets the background color
		 */
		void SetBackgroud(float r, float g, float b);
		void SetBackgroud(float r, float g, float b, float alfa);

		virtual void RenderScene();

		void setBackgroud(float r, float g, float b, float alfa);
		void setBackgroud(glm::vec4 color);
		Fr_Camera&  getActiveCamera(void);

		void setupActiveCamera(const char* name, RenderInfo& info);
		void setupActiveCamera(uint8_t val, RenderInfo& info);

		void CreateDefaultCameras(void);
		
		/** Renders Text (Freetype Font)*/
		void RenderText(RenderInfo& info);

		void Render(RenderInfo& info);
		void RenderPrimativeShapes(RenderInfo& info);
 
		void RenderSilhouette(const glm::mat4& mvp);
 

		auto SearchIntersection(const glm::vec3& ray);

		std::string getUniqueName(const std::string& name, const std::vector<std::string>& names);

		SceneItemStruct CreateDefaultSunLight(void);
		uint8_t m_active_camera;

		// Function to find all occurrences of a specific type in the m_world vector

		bool replaceItemByID(int id, SceneItemStruct& newItem);
		bool deleteItemByID(int id);
		bool deleteItemByID(std::string_view str);

		
		template <typename T>
		void findOccurrencesOfType(std::vector<std::shared_ptr<T>>& vect, NODETYPE type) {
			for (const auto& sceneItem : m_world) {
				if (sceneItem.Sceneitem->isOfType(type)) {
					std::shared_ptr<T> ptr = std::static_pointer_cast<T>(sceneItem.Sceneitem);
					vect.push_back(ptr);
				}
			}
		}

		template <typename T>
		bool replaceItemByName(std::shared_ptr<T> other, std::string_view name) {
			for (auto& item : m_world) {
				if (item.name == name) {
					item.Sceneitem = other; // Assuming you want to replace the Sceneitem
					return true; // Item was found and replaced
				}
			}
			return false; // Item was not found
		}

		template <typename T>
		bool replaceItemByID(std::shared_ptr<T> other, genID id) {
			for (auto& item : m_world) {
				if (item.id == id) {
					item.Sceneitem = other; // Assuming you want to replace the Sceneitem
					return true; // Item was found and replaced
				}
			}
			return false; // Item was not found
		}

		template <typename T>
		void findItemByName(std::shared_ptr<T>& answer, const std::string_view& name) {
			for (const auto& item : m_world) {
				if (item.name == name) {
					std::shared_ptr<T> temp = std::static_pointer_cast<T>(item.Sceneitem);
					if (temp) {
						answer = temp;
						return; // Found the item, so no need to continue searching
					}
				}
			}
			answer.reset(); // Reset if not found
		}

		template <typename T>
		void findItemByID(std::shared_ptr<T>& answer, genID id) {
			for (const auto& item : m_world) {
				if (item.id == id) {
					std::shared_ptr<T> temp = std::static_pointer_cast<T>(item.Sceneitem);
					if (temp) {
						answer = temp;
						return; // Found the item, so no need to continue searching
					}
				}
			}
			answer.reset(); // Reset if not found
		}



		void add3DObject(std::string fName = "");
		void addObject(SceneItemStruct&& item);
		void addObject(std::shared_ptr<Fr_Widget> item, std::string name = "NoName");

		void delete3DObject(std::shared_ptr<Fr_Widget> item);
		void delete3DObject(SceneItemStruct& obj);
		SceneItemStruct CreateGrid();
		SceneItemStruct CreateAxis();

		//Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
		void setupScene();

		/**
		 * Handel events coming from GLFW window and distribute it to the registered objects inside the Scene.
		 *
		 * \param ev    Incoming events from GLFW window
		 * \return      One if no events remained and all consumed, 0 if the events needs further treatment
		 */
		int handle(int ev);
		Fr_Camera m_cameras[TOTAL_CAMS];
		std::vector<SceneItemStruct> m_world;
		protected:
			ray_t activeRay; 
	private:
		glm::vec4 m_Background;
	};
}
#endif
