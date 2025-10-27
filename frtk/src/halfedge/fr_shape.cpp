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

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <halfedge/fr_shape.h>
#include "fr_shape.h"

namespace FR {
	static const glm::mat4 kShadowMapBiasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);

	Fr_Shape::Fr_Shape(const std::string& fpath, glm::vec4 color, float silhouette) :Fr_Widget(NULL, NULL, "Shape")
		{
		if (!m_shader) {
			m_shader = std::make_shared<Shader_t>();
		}
		if (std::filesystem::exists(fpath))
		{
		ReadFile(fpath); //Read vertices 
	}
		else if (fpath.substr(0, 3) == "OFF") {
			ReadMeshString(fpath);
		}
		else {
			assert("ERROR: No mesh provided to the class");
		}
		init(); //This will initializes all Openmesh, vertices, edget ..etc
		m_label.text = "Widget";
		//m_label.visible = true;   User should do this manually
	}
#if 0 //For debugging only

	void printCharacterAsDots(FT_GlyphSlot glyph) {
		int width = glyph->bitmap.width;
		int height = glyph->bitmap.rows;

		// Loop through each pixel in the bitmap
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				uint8_t alpha = glyph->bitmap.buffer[y * width + x];
				// Print a dot for opaque pixels, otherwise print a space
				if (alpha > 128) {
					std::cout << ".";
				}
				else {
					std::cout << " ";
				}
			}
			std::cout << std::endl; // New line for the next row
		}
	}

	void printStringAsDots(const std::string& text, FT_Face face) {
		for (char c : text) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				std::cerr << "Failed to load Glyph: " << c << std::endl;
				continue;
			}
			std::cout << "Character: " << c << std::endl;
			printCharacterAsDots(face->glyph);
			std::cout << std::endl; // Space between characters
		}
	}
#endif

	//Default constructor with no vertices defined
	Fr_Shape::Fr_Shape() : Fr_Widget(NULL, NULL, "") {
	}

	Fr_Shape::~Fr_Shape() {
		//Think about cleanup here ?????

/*		if (m_vao != 0) {
			glCheckFunc(glDeleteVertexArrays(1, &m_vao));
			glCheckFunc(glDeleteBuffers(NUM_OF_VBO_BUFFERS, m_vbo));
		}
		*/

		for (auto& pair : Characters)
			glDeleteTextures(1, &pair.second.TextureID);
	}

	void Fr_Shape::draw() {
		glCheckFunc(glBindVertexArray(m_vao));
		glCheckFunc(glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0));
		glCheckFunc(glBindVertexArray(0));
	}

	void Fr_Shape::calculateTextCoor( ) {
		// Add a new property for storing UV coordinates (per-face UVs)
		OpenMesh::FPropHandleT<OpenMesh::Vec2f> texcoord;
		m_mesh.add_property(texcoord, "texcoord");

		// Calculate UV coordinates for each face
		for (auto fh : m_mesh.faces()) {
			std::vector<MyMesh::Point> facePoints;

			// Collect all vertices of the face
			for (auto vh : m_mesh.fv_range(fh)) {
				facePoints.push_back(m_mesh.point(vh));
			}

			// Calculate the UV coordinates for each vertex in the face
			for (size_t i = 0; i < facePoints.size(); ++i) {
				float u = (facePoints[i][0] - m_boundBox->minX()) / (m_boundBox->Xlength());
				float v = (facePoints[i][1] - m_boundBox->minY()) / (m_boundBox->Ylength());

				// Store the UV coordinates
				m_textcoord.emplace_back(abs(u));
				m_textcoord.emplace_back(abs(v));
			}
		}
	}

	void Fr_Shape::LoadLights(std::shared_ptr<ShaderProgram> program, const std::vector<LightInfo>& lights) {
		unsigned int nlights =(unsigned int)(std::min(lights.size(), kMaxLights));
		program->SetUniformInteger("nlights", nlights);
		for (size_t i = 0; i < nlights; ++i) {
			auto uniformVarNameInObjShader = "lights[" + std::to_string(i) + "].";
			program->SetUniformVec4(uniformVarNameInObjShader + "color", lights[i].lightcolor);
			program->SetUniformVec4(uniformVarNameInObjShader + "position", lights[i].position);       //Here we send the name of the variable as "lights[xxx=number]." wher xxx= a number from 0 to nlights
			program->SetUniformVec4(uniformVarNameInObjShader + "diffuse", lights[i].diffuse);
			program->SetUniformVec4(uniformVarNameInObjShader + "specular", lights[i].specular);
			program->SetUniformVec4(uniformVarNameInObjShader + "ambient", lights[i].ambient);
			program->SetUniformVec3(uniformVarNameInObjShader + "attenuation", lights[i].attenuation);
			program->SetUniformInteger(uniformVarNameInObjShader + "is_spot", lights[i].is_spot);
			program->SetUniformVec3(uniformVarNameInObjShader + "direction", lights[i].direction);
			program->SetUniformFloat(uniformVarNameInObjShader + "cutoff", lights[i].cutoff);
			program->SetUniformFloat(uniformVarNameInObjShader + "exponent", lights[i].exponent);
			program->SetUniformCamPosition("camPos");
		}
	}

	void Fr_Shape::Render(RenderInfo& info) {
		if (!m_active ||
			(info.render_transparent && m_color.a == 1) ||
			(!info.render_transparent && m_color.a < 1))
			return;
		auto mvp = info.projection * info.modelview * m_Matrix;
 
		if (m_color.a == 1)
			RenderSilhouette(mvp);
 
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

	void Fr_Shape::RenderSilhouette(const glm::mat4& mvp) {
		if (!m_active)
			return;
		m_shader->silhouette_prog->Enable();
		m_shader->silhouette_prog->SetAttribLocation("position", 0);
		m_shader->silhouette_prog->SetAttribLocation("normal", 1);

		m_shader->silhouette_prog->SetUniformFloat("silhouette", silhouette_);
		m_shader->silhouette_prog->SetUniformMat4("mvp", mvp);

		glCheckFunc(glEnable(GL_CULL_FACE));
		glCheckFunc(glCullFace(GL_FRONT)  ); // draw only backfaces

		draw();
		m_shader->silhouette_prog->Disable();
		//back to normal
		glCheckFunc(glCullFace(GL_BACK));          // restore normal culling
		glCheckFunc(glDisable(GL_CULL_FACE));      // or disable if not used elsewhere
		glCheckFunc(glDisable(GL_STENCIL_TEST));   // if you used it
		glCheckFunc(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL)); // ensure back to normal
		glCheckFunc(glDepthFunc(GL_LESS));         // default depth test
	}

	void Fr_Shape::lbl_redraw()
	{
		if (!m_label.fnFont) {
			//Font is not defined, do nothing 
			FRTK_CORE_ERROR("ERROR: Label draw when font is not defined\n");
			return;// do nothing
		}
	}

	void Fr_Shape::RenderText(RenderInfo& info) {
		glCheckFunc(glDisable(GL_DEPTH_TEST)); // Without disabling this, text over text will not be transparent in the scene
		glCheckFunc(glEnable(GL_BLEND));
		glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_shader->txtFont_program->Enable();
		m_shader->txtFont_program->SetUniformVec3("textColor", m_label.color);
		glCheckFunc(glActiveTexture(GL_TEXTURE0));
		glCheckFunc(glBindVertexArray(m_vao_txt));

		glm::mat4 mvp;

		// Positioning text at the top corner 
		float x = m_label.offset.x + m_boundBox->minX();
		float y = m_label.offset.y + m_boundBox->maxY();
		float z = m_label.offset.z + m_boundBox->minZ();
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(x, y, z)); // Translate to position
		model = model*glm::scale(model, glm::vec3(m_label.scale, m_label.scale, 1.0f)); // Scale uniformly
		if (m_label.type == ORTHOGRAPHIC) {
			mvp = glm::ortho(0.0f, (float)info.screenDim.w, 0.0f, (float)info.screenDim.h);
		}
		else {
			mvp = info.projection* info.modelview * model;// Perspective
		}
		m_shader->txtFont_program->SetUniformMat4("mvp", mvp);

		x = 0;
		y = 0;
		for (auto c : m_label.text) {
			Character_t ch = Characters[c];

			// Position calculations based on character metrics
			float xpos = x + ch.Bearing.x;  
			float ypos = y - (ch.Size.y - ch.Bearing.y);

			float w = ch.Size.x ;  
			float h = ch.Size.y ;  

			float vertices[6][4] = {
				{ xpos + w, ypos + h,   1.0f, 0.0f }, // Top-right
				{ xpos,     ypos,       0.0f, 1.0f }, // Bottom-left
				{ xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
				{ xpos + w, ypos + h,   1.0f, 0.0f }, // Top-right (repeat)
				{ xpos,     ypos,       0.0f, 1.0f }, // Bottom-left (repeat)
				{ xpos + w, ypos,       1.0f, 1.0f }  // Bottom-right
			};

			// Bind the texture for the current character
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);

			// Update vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_TEXT_VB]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance the cursor for the next character
			x += (ch.Advance >> 6) ; 
		}

		// Clean up
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		m_shader->txtFont_program->Disable();
	}

	/*
		Hints : how to extract indicies from openmesh
		typedef OpenMesh::PolyMesh_ArrayKernelT<> MyMesh;

		int main() {
			MyMesh mesh;

			// Add vertices to the mesh
			MyMesh::VertexHandle v1 = mesh.add_vertex(MyMesh::Point(0.0, 0.0, 0.0));
			MyMesh::VertexHandle v2 = mesh.add_vertex(MyMesh::Point(1.0, 0.0, 0.0));
			MyMesh::VertexHandle v3 = mesh.add_vertex(MyMesh::Point(0.0, 1.0, 0.0));

			// Create a face
			mesh.add_face(v1, v2, v3);

			// Extract vertex indices
			std::vector<unsigned int> vertexIndices;
			for (const auto& vh : mesh.vertices()) {
				vertexIndices.push_back(vh.idx());
			}

			// Extract face indices
			std::vector<unsigned int> faceIndices;
			for (const auto& face : mesh.faces()) {
				for (const auto& vh : mesh.fv(face)) {
					faceIndices.push_back(vh.idx());
				}
			}

			// Output indices
			std::cout << "Vertex Indices:" << std::endl;
			for (const auto& idx : vertexIndices) {
				std::cout << idx << " ";
			}
			std::cout << std::endl;

			std::cout << "Face Indices:" << std::endl;
			for (const auto& idx : faceIndices) {
				std::cout << idx << " ";
			}
			std::cout << std::endl;

			return 0;

	*/
}