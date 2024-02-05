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
//	This id  generator is inspired by HAZEL ENGINE THE CHERNO
//  Modified by Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#ifndef FR_GENID_H
#define FR_GENID_H
#include <../src/frtk.h>
#include< ../src/Fr_Core.h>

namespace FR {

	class genID
	{
	public:
		genID();
		genID(uint64_t u);
		genID(const genID&) = default;

		operator uint64_t() const { return m_genID; }
	private:
		uint64_t m_genID;
	};
}

namespace std {
	template <typename T> struct hash;

	template<>
	struct hash<FR::genID>
	{
		std::size_t operator()(const FR::genID& val) const
		{
			return (uint64_t)val;
		}
	};
}


#endif