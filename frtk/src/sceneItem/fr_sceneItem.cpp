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


// Class to manage the collection of SceneObjStruct instances
template <typename T>
class MeshManager {
private:
    std::vector<SceneObjStruct<T>> sceneObjects;

public:
    // Add a new SceneObjStruct to the collection
    void add(const T& object) {
        SceneObjStruct<T> sceneObject;
        sceneObject.SceneObj = std::make_shared<T>(object);
        sceneObject.this_inner.id = genID::generateID();
        sceneObjects.push_back(sceneObject);
    }

    // Find a SceneObjStruct by its unique identifier
    SceneObjStruct<T>* findByID(uint64_t id) {
        auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(),
            [id](const SceneObjStruct<T>& obj) { return obj.this_inner.id == id; });

        return (it != sceneObjects.end()) ? &(*it) : nullptr;
    }

    // Replace a SceneObjStruct with a new one based on its unique identifier
    bool replaceByID(uint64_t id, const T& newObject) {
        auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(),
            [id](const SceneObjStruct<T>& obj) { return obj.this_inner.id == id; });

        if (it != sceneObjects.end()) {
            it->SceneObj = std::make_shared<T>(newObject);
            return true;
        }

        return false;
    }
    // Find a SceneObjStruct by its name
    SceneObjStruct<T>* findByName(const std::string& name) {
        auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(),
            [name](const SceneObjStruct<T>& obj) { return obj.this_inner.name == name; });

        return (it != sceneObjects.end()) ? &(*it) : nullptr;
    }

    // Replace a SceneObjStruct with a new one based on its name
    bool replaceByName(const std::string& name, const T& newObject) {
        auto it = std::find_if(sceneObjects.begin(), sceneObjects.end(),
            [name](const SceneObjStruct<T>& obj) { return obj.this_inner.name == name; });

        if (it != sceneObjects.end()) {
            it->SceneObj = std::make_shared<T>(newObject);
            return true;
        }

        return false;
    }


    // Delete a SceneObjStruct by its unique identifier
    bool deleteSceneObjectByID(int id) {
        auto it = std::remove_if(sceneObjects.begin(), sceneObjects.end(),
            [id](const SceneObjStruct<T>& obj) { return obj.this_inner.id == id; });

        if (it != sceneObjects.end()) {
            sceneObjects.erase(it, sceneObjects.end());
            return true;
        }

        return false;
    }

    // Get all SceneObjStruct instances
    const std::vector<SceneObjStruct<T>>& getAllSceneObjects() const {
        return sceneObjects;
    }
};

