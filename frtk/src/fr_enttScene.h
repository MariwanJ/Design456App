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

#include<entt.hpp>
#include<fr_camera.h>
#include<fr_genID.h>

namespace FR {

	class FRTK_API Fr_enttScene {
		friend class Fr_Module;
		friend Fr_GL3Window;
	public:
		
		Fr_enttScene() = default;
		~Fr_enttScene();
		Fr_enttScene(entt::entity ID, Fr_enttScene* scene);
		Fr_enttScene(const Fr_enttScene& other) = default;  //shallow copy of the member variables

		operator bool() const;
		operator entt::entity() const;
		operator uint32_t() const;

		

		Fr_Module createModule(const std::string& name = std::string());
		Fr_Module createModuleWithID(genID id, const std::string& name = std::string());

		void removeModule(Fr_Module moduleVal);
		//Module DuplicateModule(Module moduleVal);
		//Module copy(Module moduleVal);
		//void paste(Module moduleVal);

		Fr_Module findModuleByName(std::string_view name);
		Fr_Module getModuleByUUID(UUID uuid);

		template<typename... Components>
		auto GetAllEntitiesWith()
		{
			return m_Registry.view<Components...>();
		}
		
		void setBackgroud(float r, float g, float b, float alfa);
		void setBackgroud(glm::vec4 color);

		void setupActiveCamera(std::string name);

		void defaultCameras(void);
		void defaultSunLight(void);

		std::vector<std::shared_ptr<Camera>> cameraList; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,
		CameraList active_camera_;


	protected:
		static GLFWwindow* linkToglfw;
 
	private:
		void RenderScene();
		//Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
		void setupScene();	

	private:

		glm::vec4 m_Background;
		entt::registry m_Registry;
		std::unordered_map<genID, entt::entity> m_ModuleMap;
		std::unordered_map<genID, entt::entity> m_cameraGroupEnt;
		const char*camNames[8] = {"Perspective","Orthographic","Top","Bottom","Front","Rear","Right","Left"};
	};
}
#endif
