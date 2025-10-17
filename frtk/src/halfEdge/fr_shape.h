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

#ifndef FR_NEW_MESH_H
#define FR_NEW_MESH_H

#include<../src/frtk.h>
#include<../src/fr_core.h>
#include<../vendor/glm/glm/glm.hpp>
#include<fr_widget.h>

// -------------------- OpenMesh

namespace FR {
	typedef struct {
		GLuint TextureID;
		glm::ivec2 Size;
		glm::ivec2 Bearing;
		GLuint Advance;
	}Character_t;

	class Fr_Shape : public Fr_Widget {
	public:
		// Constructors
		Fr_Shape(const std::string& path, glm::vec4 color = glm::vec4(FR_GRAY), float silhouette = 0.05);
		Fr_Shape(); // Default constructor

		// Destructor
		~Fr_Shape();

		// Public Methods
		void Draw();
		void SetVertexes(std::vector<float>& vertices, std::vector<unsigned int>& indices);
		glm::vec3 GetVertex(unsigned int index, const float vertices[]);
		void ReadFile(const std::string& path);

		// Shared Pointer
		std::shared_ptr<Fr_Texture2D> m_Texture2D;
		void Render(RenderInfo& info) override;
		void RenderText(RenderInfo& info) override;
		
	private:
		bool normalized_;
		Fr_Window* linktoMainWindow;

		// Private Methods
		void calculateTextCoor() override;
		void LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights);
		void RenderSilhouette(const glm::mat4& mvp);
		
		void lbl_redraw() override;

		// Constants
		const size_t kMaxLights = 8; // Important for light calculations

		// Shared between instances


		// Attributes
		float silhouette_;



		//this should be 
		std::map<char, Character_t> Characters;

	};
}
#endif
