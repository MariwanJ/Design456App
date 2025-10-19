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

#include <ft2build.h>
#include FT_FREETYPE_H 


namespace FR {
	static const glm::mat4 kShadowMapBiasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0);


	Fr_Shape::Fr_Shape(const std::string& path, glm::vec4 color, float silhouette) :Fr_Widget(NULL, NULL, path)
		{
		if (!m_shader) {
			m_shader = std::make_shared<Shader_t>();
		}
			std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/";
			m_shader->wdg_prog = std::make_shared <ShaderProgram>       (shaderpath+"wdgshader");
			m_shader->silhouette_prog = std::make_shared <ShaderProgram>(shaderpath+"silhouette");
			m_shader->texture_prog = std::make_shared <ShaderProgram>   (shaderpath+"texture");
			m_shader->widgPoits_prog= std::make_shared <ShaderProgram>  (shaderpath+"widgPoints");
			m_shader->txtFont_program = std::make_shared <ShaderProgram>(shaderpath + "txtFont");
			
		ReadFile(path);
		m_boundBox = std::make_shared <cBoundBox3D>();
		m_boundBox->setVertices(m_vertices);
		m_label.fnFont = std::make_shared <std::string>(fontPath + "OpenSansRegular.ttf"); // DEFAULT FONT 
		m_label.text = "Shape - Be happy!!!";
		m_label.visible = true;
		m_label.scale = 1.0f;
		calcualteTextCoor(1024, 1024);
		initializeVBO();
		CreateShader();

		FT_Library ft = NULL;
		assert(FT_Init_FreeType(&ft) == 0, "ERROR::FREETYPE: Could not init FreeType Library\n");

		FT_Face face = NULL;
		if (FT_New_Face(ft, m_label.fnFont->c_str(), 0, &face)) {
			FT_Done_FreeType(ft);
			assert("ERROR::FREETYPE: Failed to load font\n");
		}

		FT_Set_Pixel_Sizes(face, m_label.pixelSize, m_label.pixelSize);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		for (unsigned char c = 0; c < 128; ++c) {
			if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
				FRTK_CORE_ERROR("Failed to load Glyph:{} ", c);
				continue;
			}
			
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			GLuint tex;
			glGenTextures(1, &tex);
			glBindTexture(GL_TEXTURE_2D, tex);
			glTexImage2D(
					GL_TEXTURE_2D, 
					0,
				    GL_RED, 
					face->glyph->bitmap.width,
					face->glyph->bitmap.rows, 
					0, 
					GL_RED, 
					GL_UNSIGNED_BYTE,
					face->glyph->bitmap.buffer);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			Character_t ch = {
				tex,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				(GLuint)face->glyph->advance.x
			};
			Characters.insert(std::pair<char, Character_t>(c, ch));
		}

		glBindTexture(GL_TEXTURE_2D, 0);
		FT_Done_Face(face);
		FT_Done_FreeType(ft);

	}
	//Default constructor with no vertices defined
	Fr_Shape::Fr_Shape() : Fr_Widget(NULL, NULL, "") {
		for (auto& pair : Characters)
			glDeleteTextures(1, &pair.second.TextureID);
	}

	Fr_Shape::~Fr_Shape() {
		//Think about cleanup here 

/*		if (m_vao != 0) {
			glCheckFunc(glDeleteVertexArrays(1, &m_vao));
			glCheckFunc(glDeleteBuffers(NUM_OF_VBO_BUFFERS, m_vbo));
		}
		*/
	}

	void Fr_Shape::Draw() {
		glCheckFunc(glBindVertexArray(m_vao));
		glCheckFunc(glDrawElements(GL_TRIANGLES, m_indices->size(), GL_UNSIGNED_INT, 0));
		glCheckFunc(glBindVertexArray(0));
	}

	void Fr_Shape::ReadFile(const std::string& path) {
		if (!m_vertices) {
			m_vertices = std::make_shared < std::vector<float>>();
		}
		if (!m_indices) {
			m_indices = std::make_shared < std::vector<unsigned int>>();
		}
		if (!OpenMesh::IO::read_mesh(m_mesh, path))
		{
			throw std::runtime_error("Failed to read mesh from " + path);
		}

		// Reserve space for vertices and indices
		m_vertices->reserve(m_mesh.n_vertices() * 3);
		m_indices->reserve(m_mesh.n_faces() * 3); // TODO: We need to make sure there are only 3 vert/obj

		// Obtain the vertex positions from the mesh
		for (auto vit = m_mesh.vertices_begin(); vit != m_mesh.vertices_end(); ++vit) {
			MyMesh::Point p = m_mesh.point(*vit);
			m_vertices->emplace_back(static_cast<float>(p[0]));
			m_vertices->emplace_back(static_cast<float>(p[1]));
			m_vertices->emplace_back(static_cast<float>(p[2]));
		}

		// Obtain the face indices from the mesh
		for (auto fit = m_mesh.faces_begin(); fit != m_mesh.faces_end(); ++fit) {
			for (auto fvit = m_mesh.fv_iter(*fit); fvit; ++fvit) {
				m_indices->emplace_back(fvit.handle().idx());
			}
		}
		init();//We should call this as the widget didn't get info from the beginign about vertices.
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
		//
		//program->Disable();
		//info.id++;
		m_shader->wdg_prog->SetUniformInteger("hasTexture", hasTexture());
		Draw();      //You should make a draw call to get that  done
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

		Draw();
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
		glCheckFunc(glEnable(GL_BLEND));
		glCheckFunc(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_shader->txtFont_program->Enable();
		m_shader->txtFont_program->SetUniformVec3("textColor", m_label.color);
		glCheckFunc(glActiveTexture(GL_TEXTURE0));
		glCheckFunc(glBindVertexArray(m_vao_txt));

		glm::mat4 mvp;

		if (m_label.type == ORTHOGRAPHIC) {
			mvp = glm::ortho(0.0f, (float)info.screenDim.w, 0.0f, (float)info.screenDim.h)* info.modelview;
		}
		else {
			mvp = info.projection * info.modelview; // Perspective
		}


		// Positioning text
		float x = m_label.offset.x + m_boundBox->minX();
		float y = m_label.offset.y + m_boundBox->maxY();
		float z = m_label.offset.z + m_boundBox->minZ();
		glm::mat4 model = glm::mat4{ 1.f };
		model =glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
		mvp = mvp * model;
		m_shader->txtFont_program->SetUniformMat4("mvp", mvp);
	
		x = 0;
		y = 0;
		for (auto c : m_label.text) {
			Character_t ch = Characters[c];

			// Position calculations based on character metrics
			float xpos = x + ch.Bearing.x*m_label.scale;  
			float ypos = y - (ch.Size.y - ch.Bearing.y);

			float w = ch.Size.x * m_label.scale; // Use original size
			float h = ch.Size.y * m_label.scale; // Use original size

			float vertices[6][4] = {
				{ xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
				{ xpos,     ypos,       0.0f, 1.0f }, // Bottom-left
				{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom-right
				{ xpos,     ypos + h,   0.0f, 0.0f }, // Top-left
				{ xpos + w, ypos,       1.0f, 1.0f }, // Bottom-right
				{ xpos + w, ypos + h,   1.0f, 0.0f }  // Top-right
			};

			// Bind the texture for the current character
			glBindTexture(GL_TEXTURE_2D, ch.TextureID);

			// Update vertex buffer
			glBindBuffer(GL_ARRAY_BUFFER, m_vbo[TEXT_VB]);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			// Draw the character
			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance the cursor for the next character
			x += (ch.Advance >> 6) * m_label.scale; // Adjust for the next character position
		}

		// Clean up
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		m_shader->txtFont_program->Disable();
	}


}