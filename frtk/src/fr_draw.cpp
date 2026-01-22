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
//
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <fr_draw.h>
#include <fr_core.h>
#include <fr_widget.h>
#include <frtk.h>

namespace FR {
	void Fr_Widget::draw_2d_sel(void) {
		//visualization of selection
		twodType_t type;
		switch (m_currentSelMode) {
		case SelectionMode::Face: {
			glCheckFunc(glBindVertexArray(m_sel_vao.faces));
			type = FR_TRIANGLE;
		}break;
		case SelectionMode::Edge: {
			glCheckFunc(glBindVertexArray(m_sel_vao.edges));
			type = FR_OPEN_LOOP;

		}break;
		case SelectionMode::Vertex: {
			glCheckFunc(glBindVertexArray(m_sel_vao.vertex));
			type = FR_POINT;
		}break;
		default: {
			type = FR_NOT_DEFINED;			// Do nothing, it i already done.
		}break;
		}
		glCheckFunc(glLineWidth(m_lineWidth));
		switch (type) {
		case FR_POINT: {
				glCheckFunc(glEnable(GL_PROGRAM_POINT_SIZE));
				glCheckFunc(glPointSize(m_pointSize));
				glCheckFunc(glDrawArrays(GL_POINTS, 0, m_selectionData.vertices.size() / 3));
			}break;
			
		case FR_LINES: {
				glCheckFunc(glDrawElements(GL_LINES, (int)m_selectionData.indices.size(), GL_UNSIGNED_INT, 0));
			}break;
			case FR_OPEN_LOOP: {
				glCheckFunc(glDrawElements(GL_LINE_LOOP, (int)m_selectionData.indices.size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!
			}break;
			case FR_TRIANGLE: {  //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
				glCheckFunc(glDrawElements(GL_TRIANGLES, (int)m_selectionData.indices.size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!            break;
			}break;
			case FR_CLOSED_LOOP: {  //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
				glCheckFunc(glDrawElements(GL_TRIANGLE_FAN, (int)m_selectionData.indices.size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!            break;
			}break;
			case FR_CIRCLE: {
				FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
			}break;
			case FR_CURVE: {
				FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
			}break;
			case FR_ARC: {
				FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
			}break;
			case FR_BSPLINE: {
				FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
				break;
			}
		}
		if (type == FR_NOT_DEFINED)
			return;
		glCheckFunc(glBindVertexArray(0));
	}

	void Fr_Widget::draw_2d(void)
	{
		glCheckFunc(glBindVertexArray(m_vao));
		glCheckFunc(glLineWidth(m_lineWidth));
		switch (lineType()) {
		case FR_POINT: {
		}
		case FR_LINES: {
			glCheckFunc(glDrawElements(GL_LINES, (int)m_indices->size(), GL_UNSIGNED_INT, 0));
		}break;
		case FR_OPEN_LOOP: {
			glCheckFunc(glDrawElements(GL_LINE_LOOP, (int)m_indices->size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!
		}break;
		case FR_CLOSED_LOOP: {  //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
			glCheckFunc(glDrawElements(GL_TRIANGLE_FAN, (int)m_indices->size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!            break;
		}break;
		case FR_TRIANGLE: {  //This includes square, rectangle, triangle,pentagon, hexagon, star ..etc
			glCheckFunc(glDrawElements(GL_TRIANGLES, (int)m_selectionData.indices.size(), GL_UNSIGNED_INT, 0));    //TODO: Check if this is correct!!            break;
		}break;
		case FR_CIRCLE: {
			FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
		}break;
		case FR_CURVE: {
			FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
		}break;
		case FR_ARC: {
			FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
		}break;
		case FR_BSPLINE: {
			FRTK_CORE_INFO("NOT IMPLEMENTED YET!");
			break;
		}
		}
		glCheckFunc(glBindVertexArray(0));
	}

	void Fr_Widget::DrawPoints() {
		glCheckFunc(glBindVertexArray(m_sel_vao.vertex));
		glCheckFunc(glPointSize(m_pointSize)); // Set the size of the points
		glCheckFunc(glDrawArrays(GL_POINTS, 0, m_vertices->size() / 3));
		glBindVertexArray(0);
	}

	void Fr_Widget::lbl_Draw()
	{
	}
	//Label Draw and Font rendering
	void Fr_Widget::lbl_draw()
	{
		return; //do nothing should be sub-classed
	}

	void Fr_Widget::pointSize(float val)
	{
		m_pointSize = val;
	}

	float Fr_Widget::pointSize()
	{
		return m_pointSize;
	}

	void Fr_Widget::lineWidth(float wid)
	{
		m_lineWidth = wid;
	}

	float Fr_Widget::lineWidth()
	{
		return m_lineWidth;
	}
	
	void Fr_Widget::initSelectionVAOs()
	{
		// Faces
		glBindVertexArray(m_sel_vao.faces);
		glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.faces);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_sel_vbo.faces_indices);

		// Edges
		glBindVertexArray(m_sel_vao.edges);
		glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.edges);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_sel_vbo.edges_indices);

		// Vertices
		glBindVertexArray(m_sel_vao.vertex);
		glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.vertex);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		glBindVertexArray(0);
	}


	void Fr_Widget::createBuffers(void)
	{

		glCheckFunc(glGenBuffers(NUM_OF_VBO_BUFFERS, m_vbo));

		glCheckFunc(glGenVertexArrays(1, &m_vao));
		glCheckFunc(glGenVertexArrays(1, &m_sel_vao.vertex));
		glCheckFunc(glGenVertexArrays(1, &m_sel_vao.edges));
		glCheckFunc(glGenVertexArrays(1, &m_sel_vao.faces));


	    glGenBuffers(1, &m_sel_vbo.faces);
		glGenBuffers(1, &m_sel_vbo.faces_indices);
		glGenBuffers(1, &m_sel_vbo.edges);
		glGenBuffers(1, &m_sel_vbo.edges_indices);
		glGenBuffers(1, &m_sel_vbo.vertex);

	}

	int Fr_Widget::initializeVBO_Selection() {
		m_selectionData.indices.clear();
		m_selectionData.vertices.clear();

		if (m_mesh.has_face_sel() > 0) {
			unsigned int indexCounter = 0;
			unsigned int i = 0;
			for (const auto& face : m_mesh.faces()) {
				if (!m_mesh.isFaceSelected(face)) continue;

				std::vector<unsigned int> localIndices;
				for (auto fv_it = m_mesh.fv_iter(face); fv_it.is_valid(); ++fv_it) {
					OpenMesh::Vec3f p = m_mesh.point(*fv_it);
					m_selectionData.vertices.push_back(p[0]);
					m_selectionData.vertices.push_back(p[1]);
					m_selectionData.vertices.push_back(p[2]);
					localIndices.push_back(indexCounter++);
				}

				// Fan triangulation
				for (size_t j = 1; j + 1 < localIndices.size(); ++j) {
					m_selectionData.indices.push_back(localIndices[0]);
					m_selectionData.indices.push_back(localIndices[j]);
					m_selectionData.indices.push_back(localIndices[j + 1]);
				}
			}
			glCheckFunc(glBindVertexArray(m_sel_vao.faces));
			glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.faces));
			glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_sel_vbo.faces_indices));
			glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_selectionData.vertices.size(), m_selectionData.vertices.data(), GL_STATIC_DRAW));
			glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_selectionData.indices.size() * sizeof(unsigned int), m_selectionData.indices.data(), GL_STATIC_DRAW));

		}
		if (m_mesh.has_edge_sel() > 0) {
			//2 Points for each edge

			unsigned int indexCounter = 0;
			for (const auto& eh : m_mesh.edges())
			{
				if (!m_mesh.isEdgeSelected(eh))
					continue;

				OpenMesh::HalfedgeHandle he0 = m_mesh.halfedge_handle(eh, 0);
				OpenMesh::HalfedgeHandle he1 = m_mesh.halfedge_handle(eh, 1);

				OpenMesh::Vec3f p0 = m_mesh.point(m_mesh.from_vertex_handle(he0));
				OpenMesh::Vec3f p1 = m_mesh.point(m_mesh.from_vertex_handle(he1));

				// first point
				m_selectionData.vertices.push_back(p0[0]);
				m_selectionData.vertices.push_back(p0[1]);
				m_selectionData.vertices.push_back(p0[2]);

				// second point
				m_selectionData.vertices.push_back(p1[0]);
				m_selectionData.vertices.push_back(p1[1]);
				m_selectionData.vertices.push_back(p1[2]);
				m_selectionData.indices.push_back(indexCounter++);
				m_selectionData.indices.push_back(indexCounter++);
			}

			glCheckFunc(glBindVertexArray(m_sel_vao.edges));
			glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.edges));
			glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_sel_vbo.edges_indices));

			glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_selectionData.vertices.size(), m_selectionData.vertices.data(), GL_STATIC_DRAW));
			glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_selectionData.indices.size() * sizeof(unsigned int), m_selectionData.indices.data(), GL_STATIC_DRAW));
		}
		if (m_mesh.has_vert_sel() > 0) {
			//2 Points for each edge

			unsigned int indexCounter = 0;
			for (const auto& vh : m_mesh.vertices())
			{
				if (!m_mesh.isVertexSelected(vh)) continue;
				OpenMesh::Vec3f p = m_mesh.point(vh);
				m_selectionData.vertices.push_back(p[0]);
				m_selectionData.vertices.push_back(p[1]);
				m_selectionData.vertices.push_back(p[2]);
			}

			glCheckFunc(glBindVertexArray(m_sel_vao.vertex));
			glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_sel_vbo.vertex));
			glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_selectionData.vertices.size(), m_selectionData.vertices.data(), GL_STATIC_DRAW));
		}
		return 0;

	}
	//You must override this if you want to draw differntly
	int Fr_Widget::initializeVBO() {
		// VERTICES
		glBindVertexArray(m_vao);
		if (m_vertices)
			if (!m_vertices->empty()) {
				glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_VERTEX_VB]));
				glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices->size(), m_vertices->data(), GL_STATIC_DRAW));
				glCheckFunc(glEnableVertexAttribArray(POSITION_VERTEX_VB));
				glCheckFunc(glVertexAttribPointer(SHADER_POS_VERTEX_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL)); // m_positionVB = 0
			}

		// TEXTURE COORDINATES
		if (m_textureCoord)
			if (!m_textureCoord->empty()) {
				glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_TEXCOORD_VB]));
				glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_textureCoord->size(), m_textureCoord->data(), GL_STATIC_DRAW));
				glCheckFunc(glEnableVertexAttribArray(POSITION_TEXCOORD_VB));
				glCheckFunc(glVertexAttribPointer(SHADER_POS_TEXTURE_VB, 2, GL_FLOAT, GL_FALSE, 0, NULL)); // POSITION_TEXCOORD_VB = 2
			}

		// ELEMENTS (Indices)
		if (m_indices)
			if (!m_indices->empty()) {
				glCheckFunc(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vbo[INDICES_VB]));
				glCheckFunc(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices->size() * sizeof(unsigned int), m_indices->data(), GL_STATIC_DRAW));
			}

		// NORMALS
		if (m_normals)
			if (!m_normals->empty()) {
				glCheckFunc(glBindBuffer(GL_ARRAY_BUFFER, m_vbo[POSITION_NORMAL_VB]));
				glCheckFunc(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_normals->size(), m_normals->data(), GL_STATIC_DRAW));
				glCheckFunc(glEnableVertexAttribArray(POSITION_NORMAL_VB)); // POSITION_NORMAL_VB should correspond to the layout in your shader, typically 2
				glCheckFunc(glVertexAttribPointer(SHADER_POS_NORMAL_VB, 3, GL_FLOAT, GL_FALSE, 0, NULL)); // Corrected to use a valid offset and index
				//                glCheckFunc(glBindVertexArray(0));
			}


		return 0;
	}
}