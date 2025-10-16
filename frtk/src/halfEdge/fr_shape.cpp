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

#include <../src/halfedge/fr_shape.h>
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
			std::string shaderpath = EXE_CURRENT_DIR + "/resources/shaders/";
			m_shader->wdg_prog = std::make_shared <ShaderProgram>       (shaderpath+"objectshader");
			m_shader->silhouette_prog = std::make_shared <ShaderProgram>(shaderpath+"silhouette");
			m_shader->texture_prog = std::make_shared <ShaderProgram>   (shaderpath+"texture");
			m_shader->widgPoits_prog= std::make_shared <ShaderProgram>  (shaderpath+"widgPoints");
			m_shader->txtFont_program = std::make_shared <ShaderProgram>(shaderpath + "txtFont");
		}
		ReadFile(path);
		m_boundBox = std::make_shared <cBoundBox3D>();
		m_boundBox->setVertices(m_vertices);
		calcualteTextCoor(1024, 1024);
		initializeVBO();
		CreateShader();
	}
	//Default constructor with no vertices defined
	Fr_Shape::Fr_Shape() : Fr_Widget(NULL, NULL, "") {

		//TODO: Dont know if we should have this. you should create shaders, boundbox, caculate texture coord, and initialize vbo by yourself.
	}

	Fr_Shape::~Fr_Shape() {
		/*if (m_vao != 0) {
			glCheckFunc(glDeleteVertexArrays(1, &m_vao));
			glCheckFunc(glDeleteBuffers(NUM_OF_VBO_BUFFERS, m_vbo));
		}*/
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

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT); // draw only backfaces

		Draw();
		m_shader->silhouette_prog->Disable();
		//back to normal
		glCullFace(GL_BACK);          // restore normal culling
		glDisable(GL_CULL_FACE);      // or disable if not used elsewhere
		glDisable(GL_STENCIL_TEST);   // if you used it
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // ensure back to normal
		glDepthFunc(GL_LESS);         // default depth test
	}
}