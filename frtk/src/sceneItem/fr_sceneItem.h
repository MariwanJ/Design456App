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

#ifndef FR_SCENEITEM_H
#define FR_SCENEITEM_H
#include <frtk.h>
#include <fr_transform.h>
#include <fr_genID.h>
#include<any>

namespace FR {
    struct SceneItemStruct {
        std::shared_ptr<std::any> Sceneitem;
        uint64_t id;
        std::string name;
        //Default constructor
        SceneItemStruct(std::shared_ptr<Node> item = nullptr,
            const std::string& itemName = "NoName",
            uint64_t itemId = genID())
            : id(itemId), name(itemName) {
        }
    };

        bool deleteItemByID(std::string_view str) {
            auto it = std::remove_if(m_world.begin(), m_world.end(),
                [str](const SceneItemStruct& obj) { return obj.name == str; });

            if (it != m_world.end()) {
                m_world.erase(it, m_world.end());
                return true;
            }
            return false;
        }

        bool replaceItemByID(int id, SceneItemStruct& newItem) {
            auto it = std::find_if(m_world.begin(), m_world.end(),
                [id](const SceneItemStruct& obj) { return obj.id == id; });

            if (it != m_world.end()) {
                *it = std::move(newItem);
                return true;
            }

            return false;
        }

        // Item management functions

         // find all occurrences of a specific type of object
        std::vector<std::shared_ptr<Node>> findOccurrencesOfType(const std::type_index& type) {
            std::vector<std::shared_ptr<Node>> children;
            for (size_t i = 0; i < m_world.size(); ++i) {
                const auto& sceneItem = m_world[i];
                if (typeid(*sceneItem.Sceneitem) == type) {
                    children.push_back(sceneItem.Sceneitem);
                }
            }
            return children;
        }

        std::optional<SceneItemStruct> findItemByName(std::string_view name) {
            for (int i = 0; i < m_world.size(); i++) {
                if (m_world[i].name == name) {
                    return m_world[i];
                }
            }
            return std::nullopt; // item was not found
        }

        std::optional<SceneItemStruct> findItemByID(genID id)
        {
            SceneItemStruct resultEntity;
            for (const auto& item : m_world) {
                if (item.id == id) {
                    return const_cast<SceneItemStruct&>(item);
                }
            }
            return std::nullopt; // item was not found
        }

        void addObject(SceneItemStruct&& item) {
            m_world.push_back(std::move(item));
        }

        // Get all SceneItemStruct instances
        const std::vector<SceneItemStruct>& getAllItems() const {
            return m_world;
        }

        // Delete a SceneItemStruct by its unique identifier
        bool deleteItemByID(int id) {
            auto it = std::remove_if(m_world.begin(), m_world.end(),
                [id](const SceneItemStruct& obj) { return obj.id == id; });

            if (it != m_world.end()) {
                m_world.erase(it, m_world.end());
                return true;
            }
            return false;
        }
    
    
    };
}

#endif