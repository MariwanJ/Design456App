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
#ifndef FR_MODULE_H
#define FR_MODULE_H

#include<entt.hpp>
#include<fr_enttScene.h>
#include <fr_components.h>

namespace FR {
    /**
     * Class to make it easy to treat entt
     * since entt is just only an id, we need to convert that to a container.
     */
    class FRTK_API Fr_Item
    {
    public:
        Fr_Item() = default;
        Fr_Item(entt::entity IDval, Fr_enttScene* Scene_val);
        Fr_Item(const Fr_Item& other) = default;

        template<typename T, typename... Args>
        T& addItem(Args&&... args)
        {
            T& component = m_enttScene->m_Registry.emplace<T>(m_ID, std::forward<Args>(args)...);
 
            return component;
        }

        //template<typename T>
        //T addOrReplaceSharedItem(T item) {
        //   T comp = m_enttScene->m_Registry.emplace_or_replace<T>(m_ID, item);
        //   return comp;
        //}

        template<typename T, typename... Args>
        T& addOrReplaceItem(Args&&... args)
        {
            T& component = m_enttScene->m_Registry.emplace_or_replace<T>(m_ID, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& GetItem()
        {
            return m_enttScene->m_Registry.get<T>(m_ID);
        }

        template<typename T>
        bool HasItem()
        {
            return m_enttScene->m_Registry.has<T>(m_ID);
        }

        template<typename T>
        void delItem()
        {
            m_enttScene->m_Registry.remove<T>(m_ID);
        }

        operator bool() const { return m_ID != entt::null; }
        operator entt::entity() const { return m_ID; }
        operator uint32_t() const { return (uint32_t)m_ID; }

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

        entt::entity m_ID{ entt::null };
        Fr_enttScene* m_enttScene = nullptr;
    };
}
#endif