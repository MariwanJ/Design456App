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
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_MESH_TOOLS_H
#define FR_MESH_TOOLS_H
namespace FR{
#include <fr_core.h>
//#include <optional>
//#include <unordered_map>

    enum class SplitAxis
    {
        xAxis = 0,
        yAxis = 1,
        zAxis = 2
    };

    struct SplitResult
    {
        Mesh first;  
        Mesh second;
    };


    SplitResult splitMesh(
        const Mesh& mesh,
        SplitAxis axis,
        std::optional<float> splitPos = std::nullopt)
    {
        SplitResult result;

        const int axisIdx = static_cast<int>(axis);

        // Compute bounding box
        OpenMesh::Vec3f bbMin(FLT_MAX, FLT_MAX, FLT_MAX);
        OpenMesh::Vec3f bbMax(-FLT_MAX, -FLT_MAX, -FLT_MAX);

        for (auto vh : mesh.vertices())
        {
            const auto p = mesh.point(vh);
            bbMin.minimize(p);
            bbMax.maximize(p);
        }

        // Use center if no explicit position supplied
        const float plane =
            splitPos.has_value()
            ? *splitPos
            : (bbMin[axisIdx] + bbMax[axisIdx]) * 0.5f;

        std::unordered_map<int, Mesh::VertexHandle> firstMap;
        std::unordered_map<int, Mesh::VertexHandle> secondMap;

        for (auto fh : mesh.faces())
        {
            bool allFirst = true;
            bool allSecond = true;

            for (auto fv : mesh.fv_range(fh))
            {
                const float value = mesh.point(fv)[axisIdx];

                allFirst &= (value <= plane);
                allSecond &= (value >= plane);
            }

            // Face crosses split plane -> discard
            if (!allFirst && !allSecond)
                continue;

            Mesh& target = allFirst ? result.first : result.second;
            auto& map = allFirst ? firstMap : secondMap;

            std::vector<Mesh::VertexHandle> faceVerts;
            faceVerts.reserve(3);

            for (auto fv : mesh.fv_range(fh))
            {
                const int idx = fv.idx();

                auto it = map.find(idx);
                if (it == map.end())
                {
                    auto newVH = target.add_vertex(mesh.point(fv));
                    map[idx] = newVH;
                    faceVerts.push_back(newVH);
                }
                else
                {
                    faceVerts.push_back(it->second);
                }
            }

            target.add_face(faceVerts);
        }

        return result;
    }

    /*
    
    // Split in the middle along X
        auto halves = splitMesh(mesh, SplitAxis::X);

     // Split at X = 25.0
        auto halves = splitMesh(mesh, SplitAxis::X, 25.0f);

    // Split in the middle along Z
        auto halves = splitMesh(mesh, SplitAxis::Z);

        // Split at Z = 0 (ground plane)
        auto halves = splitMesh(mesh, SplitAxis::Z, 0.0f);

    
    */
}
#endif// FR_MESH_TOOLS_H
