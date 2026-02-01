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
#ifndef FR_OPENMESH_H
#define FR_OPENMESH_H

#include <OpenMesh/Core/Mesh/PolyMesh_ArrayKernelT.hh>
#include <OpenMesh/Core/IO/MeshIO.hh>
#include <OpenMesh/Core/Utils/PropertyManager.hh>

namespace FR {
    typedef OpenMesh::MeshHandle MeshHandle;
    typedef OpenMesh::FaceHandle FaceHandle;
    typedef OpenMesh::EdgeHandle EdgeHandle;
    typedef OpenMesh::VertexHandle VertexHandle;
    
    typedef enum MeshType {
        REAL_MESH,
        FAKE_MESH
    }MeshType;
    class FrOpenMesh : public OpenMesh::PolyMesh_ArrayKernelT<>
    {
    public:
        // Property handles
        OpenMesh::MPropHandleT<bool> mesh_selected;
        OpenMesh::VPropHandleT<bool> v_selected;
        OpenMesh::EPropHandleT<bool> e_selected;
        OpenMesh::FPropHandleT<bool> f_selected;
        OpenMesh::HPropHandleT<bool> h_selected;

        OpenMesh::MPropHandleT<bool> m_fake;
        OpenMesh::VPropHandleT<bool> v_fake;  
        OpenMesh::EPropHandleT<bool> e_fake;  
        OpenMesh::FPropHandleT<bool> f_fake;  

        
        MeshType m_meshType;
        FrOpenMesh(MeshType type = MeshType::REAL_MESH);
        ~FrOpenMesh();

        // Mesh
        void selectMesh(bool s);
        void toggleMeshSelection();
        bool isMeshSelected() const;

        // Vertex
        void selectVertex(VertexHandle v, bool s);
        void toggleVertexSelection(VertexHandle v);
        bool isVertexSelected(VertexHandle v) const;

        // Edge
        void selectEdge(EdgeHandle e, bool s);
        void toggleEdgeSelection(EdgeHandle e);
        bool isEdgeSelected(EdgeHandle e) const;

        // Face
        void selectFace(FaceHandle f, bool s);
        void toggleFaceSelection(FaceHandle f);
        bool isFaceSelected(FaceHandle f) const;

        // Halfedge
        void selectHalfedge(HalfedgeHandle h, bool s);
        void toggleHalfeedgeSelection(HalfedgeHandle h);
        bool isHalfedgeSelected(HalfedgeHandle h) const;

        size_t has_vert_sel();
        size_t has_edge_sel();
        size_t has_face_sel();

        void clearAllSelections();
        void initializeFakeFlags();

        bool isFake() const;
        void isFake(bool val);

    private:
        size_t m_has_vert_sel;
        size_t m_has_edge_sel;
        size_t m_has_face_sel;
    };
}
#endif //#define FR_OPENMESH_H
