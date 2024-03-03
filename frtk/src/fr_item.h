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
#ifndef FR_ITEM_H
#define FR_ITEM_H

#include <../vendor/Flecs/src/flecs.h>
#include <fr_enttScene.h>
#include <fr_components.h>

namespace FR {

    class FRTK_API Fr_Item
    {
    public:
        Fr_Item() = default;
        Fr_Item(flecs::entity IDval, Fr_enttScene* Scene_val);
        Fr_Item(const Fr_Item& other) = default;

        template<typename T, typename... Args>
        T& addItem(Args&&... args) {
            return m_enttScene->m_world.emplace<T>(m_ID, std::forward<Args>(args)...);
        }


        template<typename T, typename... Args>
        T& addOrReplaceItem(Args&&... args)
        {
            T& component = m_enttScene->get_registry().set<T>(m_ID, std::forward<Args>(args)...);
            return component;
        }


        template<typename T>
        T& GetItem() {
            return m_enttScene->m_world.get<T>(m_ID);
        }




        template<typename T>
        bool HasItem() {
            return m_enttScene->m_world.has<T>(m_ID);
        }

        template<typename T>
        void delItem() {
            m_enttScene->m_world.remove<T>(m_ID);
        }

        operator bool() const { return m_ID.is_valid(); }
        operator flecs::entity() const { return m_ID; }
        operator uint32_t() const { return m_ID; }

        genID GetUUID() { return GetItem<ItemID>().ID; }
        const std::string& GetName() { return GetItem<ItemName>().m_Name; }

        bool operator==(const Fr_Item& val) const
        {
            return m_ID == val.m_ID && m_enttScene == val.m_enttScene;
        }

        bool operator!=(const Fr_Item& other) const
        {
            return !(*this == other);
        }

    private:
        flecs::entity m_ID;
        Fr_enttScene* m_enttScene = nullptr;
    };
}
#endif
