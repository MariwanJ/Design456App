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

#include<fr_menu.h>
#include<fr_toolbar.h>
#include <glm/gtx/string_cast.hpp>
#include<Math/fr_math.h>
#include<fr_constants.h>
#include<fr_window.h>
//TODO FIX ME DOSENT WORK DON'T KNOW WHY
namespace FR {
	int Fr_Window::imguimzo_init()
	{
		return 0;
	}

	/************************
	*   Contains all ImGUI and ImGuimzo functions
	*/
	int Fr_Window::renderimGUI(userData_& data) {
		static bool opt_fullscreen = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		//FR_PROFILE_FUNCTION();
		//FR_PROFILE_SCOPE("renderimGUI");

		// Get the current style
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding = ImVec2(1, 1);
		style.FramePadding = ImVec2(1, 1);
		// Your other UI code goes here
		if (imgui_menu() < 0) return -1;
		if (imgui_ToolbarPannel() < 0) return -1;
		if (imgui_LeftPanel() < 0) return -1;
		if (CamerOptionVisible) CameraOptions();
		SunOptions();
		if (showOpenDialog) createOpenDialog();
		return 1;
	}

	int Fr_Window::imgui_CameraConfiguration(userData_& data)
	{
		//Demo code fix me

		static float f = 0.0f;
		static int counter = 0;

		ImGuiWindowFlags window_flags = 0;

		ImGui::Begin("Camera Configuration!", nullptr, window_flags);                          // Create a window called "Hello, world!" and append into it.

		f = data.orthoSize_;
		ImGui::DragFloat("OrthoSize", &f, 0.2f, -1000.0f, 1000.0f);
		data.orthoSize_ = f;

		f = data.camm_position[0];
		ImGui::DragFloat("m_positionx", &f, 0.2f, -1000.0f, 1000.0f);
		data.camm_position[0] = f;
		f = data.camm_position[1];
		ImGui::DragFloat("m_positiony", &f, 0.2f, -1000.0f, 1000.0f);
		data.camm_position[1] = f;
		f = data.camm_position[2];
		ImGui::DragFloat("m_positionz", &f, 0.2f, -1000.0f, 1000.0f);
		data.camm_position[2] = f;

		f = data.direction_[0];
		ImGui::DragFloat("Target_x", &f, 0.2f, -1000.0f, 1000.0f);
		data.direction_[0] = f;
		f = data.direction_[1];
		ImGui::DragFloat("Target_y", &f, 0.2f, -1000.0f, 1000.0f);
		data.direction_[1] = f;
		f = data.direction_[2];
		ImGui::DragFloat("Target_z", &f, 0.2f, -1000.0f, 1000.0f);
		data.direction_[2] = f;

		static int type;
		f = data.aspectRatio_;
		ImGui::DragFloat("aspectratio", &f, 0.2f, 0.0f, 5);
		data.aspectRatio_ = f;

		ImGui::SliderInt("Cameratype", &type, 0, MAX_CAMERAS - 1);
		data.camType_ = (uint8_t)type;

		f = data.fovy_;
		ImGui::DragFloat("FOVY", &f, 0.2f, -120.0f, 120.0f);
		data.fovy_ = f;

		f = data.up_[0];
		ImGui::DragFloat("UP_x", &f, 0.2f, -100000.0f, 100000.0f);
		data.up_[0] = f;
		f = data.up_[1];
		ImGui::DragFloat("UP_y", &f, 0.2f, -100000.0f, 100000.0f);
		data.up_[1] = f;
		f = data.up_[2];
		ImGui::DragFloat("UP_z", &f, 0.2f, -100000.0f, 100000.0f);
		data.up_[2] = f;

		f = data.zfar_;
		ImGui::DragFloat("Far", &f, 0.2f, -10000.0f, 100000.0f);
		data.zfar_ = f;
		f = data.znear_;
		ImGui::DragFloat("Near", &f, 0.2f, -10.0f, 100000.0f);
		data.znear_ = f;

		ImGui::Text("Use the sliders to configure the camera");               // Display some text (you can use a format strings too)
		ImGui::ColorEdit3("bkg color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Reset Camera to defaults")) {                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;

			activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].setupCameraHomeValues();
			activeScene->m_cameras[(unsigned int)activeScene->m_active_camera].getUserData(data);
		}
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
		return 0;
	}
	float Fr_Window::getAspectRation() const
	{
		return Camera::m_aspect_ratio;
	}
	eventData Fr_Window::GLFWevents() const
	{
		return m_GLFWevents;
	}
	int Fr_Window::imgui_ViewPort()
	{
		activeScene->RenderScene();
		return 0;
	}

	int Fr_Window::imgui_menu()
	{
		if (ImGui::BeginMainMenuBar()) //Start creating Main Window Menu.
		{
			ImGuiStyle& style = ImGui::GetStyle();
			style.WindowMenuButtonPosition = ImGuiDir_Up; //Remove the button -- TODO: DONT KNOW IF WE SHOULD REMOVE IT!!!! 2025-02-01
			style.WindowMenuButtonPosition | ImGuiStyleVar_DockingSeparatorSize;

			if (ImGui::BeginMenu("File"))
			{
				//IMGUI_DEMO_MARKER("Examples/Menu");
				if (ImGui::MenuItem("New")) { mnuFileNew_cb(nullptr); }
				if (ImGui::MenuItem("Open", "Ctrl+O")) { mnuFileOpen_cb(nullptr); }
				if (ImGui::BeginMenu("Open Recent"))
				{
					ImGui::MenuItem("---");
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Save", "Ctrl+S")) { mnuFileSave_cb(nullptr); }
				if (ImGui::MenuItem("Save As..")) { mnuFileSaveAs_cb(nullptr); }
				ImGui::Separator();
				if (ImGui::MenuItem("Import")) { mnuFileImport_cb(nullptr); }
				if (ImGui::MenuItem("Export")) { mnuFileImport_cb(nullptr); }
				ImGui::Separator();
				if (ImGui::MenuItem("Exit", "Alt+F4")) { mnuFileExit_cb(nullptr); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) { mnuEditUndo(nullptr); }
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) { mnuEditRedo(nullptr); }  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Copy", "CTRL+C")) { mnuEditCopy(nullptr); }
				if (ImGui::MenuItem("Cut", "CTRL+X")) { mnuEditCut(nullptr); }
				if (ImGui::MenuItem("Paste", "CTRL+V")) { mnuEditPaste(nullptr); }
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Tools"))
			{
				ImGui::MenuItem("Show/Hide Camera Options", "", &CamerOptionVisible);
				ImGui::EndMenu();
			}
		}
		ImGui::EndMainMenuBar();
		return 0;
	}

	void Fr_Window::CameraOptions() {
		userData_ data;

		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiWindowFlags window_flags = 0
			| ImGuiWindowFlags_NoDocking
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_NoNavFocus
			| ImGuiWindowFlags_NoDecoration;

		activeScene->m_cameras[activeScene->m_active_camera].getUserData(data);
		imgui_CameraConfiguration(data);
		if (activeScene->m_active_camera != data.camType_) {
			activeScene->m_cameras[activeScene->m_active_camera].isActive(false);
			activeScene->m_active_camera = data.camType_;
			activeScene->m_cameras[activeScene->m_active_camera].getUserData(data);
		}
		activeScene->m_cameras[activeScene->m_active_camera].setUserData(data);
		activeScene->m_cameras[activeScene->m_active_camera].isActive(true);
	}

	void Fr_Window::SunOptions() {
		ImGui::Begin("Sun Options");
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiWindowFlags window_flags = 0
			| ImGuiWindowFlags_NoDocking
			//| ImGuiWindowFlags_NoTitleBar
		   //| ImGuiWindowFlags_NoResize
	   //   | ImGuiWindowFlags_NoMove
		  //| ImGuiWindowFlags_NoScrollbar
		  //| ImGuiWindowFlags_NoSavedSettings
			;
		std::string_view str = "Sun";
		std::shared_ptr<Fr_Light> sunT;
		activeScene->findItemByName(sunT, str);

		glm::vec4 pos = sunT->getPosition();

		float f;
		float f1, f2, f3;
		f1 = sunT->getPosition().x;
		f2 = sunT->getPosition().y;
		f3 = sunT->getPosition().z;

		f = pos[0];
		ImGui::DragFloat("Translate x", &f, 0.2, -1000.f, 1000.f);
		pos[0] = f;
		f = pos[1];
		ImGui::DragFloat("Translate y", &f, 0.2, -1000.f, 1000.f);
		pos[1] = f;
		f = pos[2];
		ImGui::DragFloat("Translate z", &f, 0.2, -1000.f, 1000.f);
		sunT->Translate(f1, f2, f3);
		pos[2] = f;

		f = pos[3];
		ImGui::DragFloat("Translate w", &f, 0.02, -1.f, 1.f);
		pos[3] = f;
		sunT->SetPosition(pos);

		auto amb = sunT->gtAmbient();
		f = amb.r;
		ImGui::DragFloat("Ambient r", &f, 0.002, 0.0f, 1.0f);
		amb.r = f;
		f = amb.g;
		ImGui::DragFloat("Ambient g", &f, 0.002, 0.0f, 1.0f);
		amb.g = f;
		f = amb.b;
		ImGui::DragFloat("Ambient b", &f, 0.002, 0.f, 1.f);
		amb.b = f;
		f = amb.a;
		ImGui::DragFloat("Ambient a", &f, 0.020, 0.f, 1.f);
		amb.a = f;
		sunT->SetAmbient(amb.r, amb.g, amb.b, amb.a);

		auto spec = sunT->getSpecular();
		f = spec.r;
		ImGui::DragFloat("specular r", &f, 0.002, 0.f, 1.f);
		spec.r = f;
		f = spec.g;
		ImGui::DragFloat("specular g", &f, 0.002, 0.f, 1.f);
		spec.g = f;
		f = spec.b;
		ImGui::DragFloat("specular b", &f, 0.002, 0.f, 1.f);
		spec.b = f;
		f = spec.a;
		ImGui::DragFloat("specular a", &f, 0.002, 0.f, 1.f);
		spec.a = f;
		sunT->SetSpecular(spec.r, spec.g, spec.b, spec.a);

		auto att = sunT->getAttenuation();
		f = att.r;
		ImGui::DragFloat("Attenuation r", &f, 0.001, 0.f, 1.f);
		att.r = f;
		f = att.g;
		ImGui::DragFloat("attv g", &f, 0.001, 0.f, 1.f);
		att.g = f;
		f = att.b;
		ImGui::DragFloat("att b", &f, 0.001, 0.f, 1.0f);
		att.b = f;
		sunT->SetAttenuation(att.r, att.g, att.b);
		ImGui::End();
	}
}