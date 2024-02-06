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

	class FRTK_API Fr_Module
	{
	public:
		Fr_Module() = default;
		Fr_Module(entt::entity IDval, Fr_enttScene* Scene_val);
		Fr_Module(const Fr_Module& other) = default;

		template<typename T, typename... Args>
		T& addModule(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace<T>(m_ID, std::forward<Args>(args)...);
			return component;
		}

		template<typename T, typename... Args>
		T& addOrReplaceModule(Args&&... args)
		{
			T& component = m_Scene->m_Registry.emplace_or_replace<T>(m_ID, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		T& GetModule()
		{
			return m_Scene->m_Registry.get<T>(m_ID);
		}

		template<typename T>
		bool HasModule()
		{
			return m_Scene->m_Registry.has<T>(m_ID);
		}

		template<typename T>
		void delModule()
		{
			m_Scene->m_Registry.remove<T>(m_ID);
		}

		operator bool() const { return m_ID != entt::null; }
		operator entt::entity() const { return m_ID; }
		operator uint32_t() const { return (uint32_t)m_ID; }

		genID GetUUID() { return GetModule<moudleID>().ID; }
		const std::string& GetName() { return GetModule<moudleName>().m_Name; }

		bool operator==(const Fr_Module& val) const
		{
			return m_ID == val.m_ID && m_enttScene == val.m_enttScene;
		}

		bool operator!=(const Fr_Module& other) const
		{
			return !(*this == other);
		}
	private:

		entt::entity m_ID;
		Fr_enttScene* m_enttScene;
	};
}
#endif