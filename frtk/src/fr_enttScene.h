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

#include<fr_camera.h>
#include<fr_light.h>
#include<fr_genID.h>
#include <sceneItem/fr_sceneItem.h>

namespace FR {

	class FRTK_API Fr_enttScene {
		friend Fr_GL3Window;
	public:

		Fr_enttScene();
		~Fr_enttScene();
		Fr_enttScene(const Fr_enttScene& other) = default;  //shallow copy of the member variables

		void setBackgroud(float r, float g, float b, float alfa);
		void setBackgroud(glm::vec4 color);

		SceneItemStruct<Camera> setupActiveCamera(std::string& name);
		SceneItemStruct<Camera> setupActiveCamera(CameraList val);

		SceneItemStruct<T> CreateDefaultCameras(void);

		void Render(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderPrimativeShapes(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderWidgetToolkit(FR::Node::RenderInfo& info, const glm::mat4& modelview);
		void RenderSilhouette(const glm::mat4& mvp);
		void RenderIMGui(FR::Node::RenderInfo& info, const glm::mat4& modelview);

		SceneItemStruct<Light> CreateDefaultSunLight(void);

		//std::vector<std::shared_ptr<Camera>> m_cameraList; //PERSPECTIVE,ORTHOGRAPHIC, TOP,BOTTOM, LEFT,RIGHT,BACK,FRONT,
		CameraList active_camera_;
		void RenderScene();

		template<typename T, typename ...Args>
		SceneItemStruct<T> createItem(std::string&& name, Args && ...args);

		SceneItemStruct<T>* findItemByID(int id);

		bool replaceItemByID(int id, const T& newItem);

		bool deleteItemByID(int id);

		SceneItemStruct<T>* findItemByName(const std::string& name);

		bool replaceItemByName(const std::string& name, const T& newItem);

		const std::vector<SceneItemStruct<T>>& getAllItems() const;

	protected:
		static Fr_GL3Window* linkToglfw;

	private:
		SceneItemStruct<Fr_Grid> CreateGrid();
		SceneItemStruct<Axis3D> CreateAxis();

		//Grid, Axis, Camera which is always created automatically.User shouldn't need to do anything
		void setupScene();

	private:

		glm::vec4 m_Background;
		std::vector<SceneItemStruct<T>> m_World;


	};
}
#endif
