//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
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
#ifndef FR_ENTTSENE_H
#define FR_ENTTSENE_H

#include<../vendor/Flecs/src/flecs.h>
#include<fr_camera.h>
#include<fr_light.h>
#include<fr_genID.h>

namespace FR {
	class testit {
	public:
		testit();
		~testit();
		std::shared_ptr<std::string> test;
		void printIt();
		std::shared_ptr<int> val;
		int w;
	};
	class FRTK_API Fr_enttScene {
		friend Fr_GL3Window;
	public:

		Fr_enttScene();
		~Fr_enttScene();
		Fr_enttScene(flecs::entity ID, Fr_enttScene* scene);
		Fr_enttScene(const Fr_enttScene& other) = default;  //shallow copy of the member variables

		flecs::entity  createItem(const std::string& name = std::string());
		flecs::entity createItemWithID(genID id, const std::string& name = std::string());

		//void removeItem(flecs::entity ItemVal);
		//Item DuplicateItem(Item ItemVal);
		//Item copy(Item ItemVal);
		//void paste(Item ItemVal);

		flecs::entity  findItemByName(std::string_view name);
		flecs::entity  getItemByUUID(genID uuid);

		//Templates
		template<typename... Components>
		auto GetAllEntitiesWith(flecs::world& world, bool includeChildren = false) {
			if (includeChildren) {
				return flecs::query<Components...>(world).iter(world, flecs::ChildOf);
			}
			else {
				return flecs::query<Components...>(world);
			}
		}

		template<typename T, typename... Args>
		T& addItem(flecs::world& w, std::string name, Args&&... args) {
			// Check if a name is provided
			if (!name.empty()) {
				// Create an entity with the given name
				flecs::entity t = w.entity(name.c_str());
				// Add the component to the entity
				t.set<T>(std::forward<Args>(args)...);
				return *t.get_mut<T>();
			}
			else {
				// Add the component to the world and return a mutable reference
				w.set<T>(std::forward<Args>(args)...);
				return *w.get_mut<T>();
			}
		}

		template<typename T, typename... Args>
		T& addOrReplaceItem(flecs::world& w, flecs::entity parentEntity, std::string name, Args&&... args) {
			// Check if a parent entity is provided
			if (parentEntity) {
				// Check if the component already exists in the parent entity
				if (parentEntity.has<T>()) {
					// Replace the existing component with the new one
					parentEntity.set<T>(std::forward<Args>(args)...);
					return *parentEntity.get_mut<T>();
				}
				else {
					// Add the component to the parent entity
					if (!name.empty()) {
						// Create an entity with the given name
						flecs::entity t = w.entity(name.c_str());
						// Add the component to the entity
						t.set<T>(std::forward<Args>(args)...);
						return *t.get_mut<T>();
					}
					else {
						parentEntity.assign<T>(std::forward<Args>(args)...);
						return *parentEntity.get_mut<T>();
					}
				}
			}
			else {
				// Check if the component already exists in the world
				if (w.has<T>()) {
					// Replace the existing component with the new one
					w.set<T>(std::forward<Args>(args)...);
					return *w.get_mut<T>();
				}
				else {
					// Add the component to the world
					if (!name.empty()) {
						// Create an entity with the given name
						flecs::entity t = w.entity(name.c_str());
						// Add the component to the entity
						t.set<T>(std::forward<Args>(args)...);
						return *t.get_mut<T>();
					}
					else {
						w.emplace<T>(std::forward<Args>(args)...);
						return *w.get_mut<T>();
					}
				}
			}
		}

		template<typename T>
		bool HasItem() {
			return m_world.has<T>(m_ID);
		}

		template<typename T>
		void delItem() {
			m_world.remove<T>(m_ID);
		}
		/*
				operator bool() const { return m_ID.is_valid(); }
				operator flecs::entity() const { return m_ID; }
				operator uint32_t() const { return m_ID; }

				bool operator==(const Fr_Item& val) const
				{
					return m_ID == val.m_ID && m_enttScene == val.m_enttScene;
				}

				bool operator!=(const Fr_Item& other) const
				{
					return !(*this == other);
				}
		*/

		void setBackgroud(float r, float g, float b, float alfa);
		void setBackgroud(glm::vec4 color);

		flecs::entity& setupActiveCamera(std::string& name);
		flecs::entity& setupActiveCamera(CameraList val);

		void CreateDefaultCameras(void);

		void Render(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderSilhouette(const glm::mat4& mvp);
		void RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview);

		void CreateDefaultSunLight(void);

		std::vector<std::shared_ptr<Camera>> cameraList; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,
		CameraList active_camera_;
		void RenderScene();

	protected:
		static Fr_GL3Window* linkToglfw;

	private:
		void CreateGrid();
		void CreateAxis();

		//Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
		void setupScene();

	private:

		glm::vec4 m_Background;
		flecs::world m_world;
	};
}
#endif
