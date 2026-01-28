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
#include <fr_openmesh.h>

namespace FR {
	FrOpenMesh::FrOpenMesh(MeshType type) : m_has_vert_sel(0), m_has_edge_sel(0), m_has_face_sel(0) , m_meshType(type)
	{
		add_property(mesh_selected, "mesh:selected");
		add_property(v_selected, "vertex:selected");
		add_property(e_selected, "edge:selected");
		add_property(f_selected, "face:selected");
		add_property(h_selected, "halfedge:selected");

		// Add property handles
		add_property(m_fake, "m_fake");
		add_property(v_fake, "v_fake");
		add_property(e_fake, "e_fake");
		add_property(f_fake, "f_fake");

		// Initialize mesh-level fake flag
		property(m_fake) = false;

		property(mesh_selected) = false;
	}

	void FrOpenMesh::initializeFakeFlags() {
		property(m_fake) = false;
		for (auto v : vertices()) property(v_fake, v) = false;
		for (auto e : edges())    property(e_fake, e) = false;
		for (auto f : faces())    property(f_fake, f) = false;
	}

	FrOpenMesh::~FrOpenMesh()
	{
		remove_property(mesh_selected);
		remove_property(v_selected);
		remove_property(e_selected);
		remove_property(f_selected);
		remove_property(h_selected);

		
		remove_property(m_fake);
		remove_property(v_fake);
		remove_property(e_fake);
		remove_property(f_fake);

	}

	void FrOpenMesh::selectMesh(bool s)
	{
		property(mesh_selected) = s;
	}

	bool FrOpenMesh::isMeshSelected() const
	{
		return property(mesh_selected);
	}

	void FrOpenMesh::selectVertex(VertexHandle v, bool s)
	{
		m_has_vert_sel++;
		property(v_selected, v) = s;
	}

	bool FrOpenMesh::isVertexSelected(VertexHandle v) const
	{
		return property(v_selected, v);
	}

	void FrOpenMesh::selectEdge(EdgeHandle e, bool s)
	{
		m_has_edge_sel++;
		property(e_selected, e) = s;
	}

	bool FrOpenMesh::isEdgeSelected(EdgeHandle e) const
	{
		return property(e_selected, e);
	}

	void FrOpenMesh::selectFace(FaceHandle f, bool s)
	{
		m_has_face_sel++;
		property(f_selected, f) = s;
	}

	bool FrOpenMesh::isFaceSelected(FaceHandle f) const
	{
		return property(f_selected, f);
	}

	void FrOpenMesh::selectHalfedge(HalfedgeHandle h, bool s)
	{
		property(h_selected, h) = s;
	}

	bool FrOpenMesh::isHalfedgeSelected(HalfedgeHandle h) const
	{
		return property(h_selected, h);
	}

	size_t FrOpenMesh::has_vert_sel()
	{
		return  m_has_vert_sel;
	}

	size_t FrOpenMesh::has_edge_sel()
	{
		return m_has_edge_sel;
	}

	size_t FrOpenMesh::has_face_sel()
	{
		return m_has_face_sel;
	}
	void FrOpenMesh::toggleMeshSelection() {
		bool sel = isMeshSelected();
		selectMesh(!sel);
	}
	void FrOpenMesh::toggleFaceSelection(FaceHandle f)
	{
		bool sel = isFaceSelected(f);
		selectFace(f, !sel);
	}
	void FrOpenMesh::toggleEdgeSelection(EdgeHandle e)
	{
		bool sel = isEdgeSelected(e);
		selectEdge(e, !sel);
	}

	void FrOpenMesh::toggleHalfeedgeSelection(HalfedgeHandle h)
	{
		bool sel = isHalfedgeSelected(h);
		selectHalfedge(h, !sel);
	}
	void FrOpenMesh::toggleVertexSelection(VertexHandle v)
	{
		bool sel = isVertexSelected(v);
		selectVertex(v, !sel);
	}

	void FrOpenMesh::clearAllSelections()
	{
		//TODO : Let's be possible to clear only one object type between all object types.
		property(mesh_selected) = false;

		for (auto v : vertices())
			property(v_selected, v) = false;

		for (auto e : edges())
			property(e_selected, e) = false;

		for (auto f : faces())
			property(f_selected, f) = false;

		for (auto h : halfedges())
			property(h_selected, h) = false;
		m_has_face_sel = m_has_edge_sel = m_has_vert_sel = 0;
	}

	bool FrOpenMesh::isFake() const { 
		return m_meshType == MeshType::FAKE_MESH; 
	}
	void FrOpenMesh::isFake(bool val) {
		if (val)
			m_meshType == MeshType::FAKE_MESH;
		else
			m_meshType == MeshType::REAL_MESH;
	}
}