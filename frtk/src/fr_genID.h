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
//    This id  generator is inspired by HAZEL ENGINE THE CHERNO
//  Modified by Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_GENID_H
#define FR_GENID_H

#include <cstdint>           // For uint64_t
#include <unordered_set>    // For std::unordered_set
#include <random>           // For std::random_device, std::mt19937_64
#include "../src/frtk.h"    // Adjusted include path (no leading /)
#include "../src/fr_core.h" // Adjusted include path (no leading /)

namespace FR {
    class FRTK_API genID {
    public:
        genID();                // Default constructor
        genID(uint64_t u);     // Constructor with specific ID
        uint64_t generate();
        genID(const genID&) = default; // Default copy constructor

        operator uint64_t() const { return m_genID; } // Conversion operator

    private:
        uint64_t m_genID;      // The generated ID

        // Static members for ID generation
        static std::random_device s_r_mDevice;
        static std::mt19937_64 s_Engine;
        static std::uniform_int_distribution<uint64_t> s_udf;
        static std::unordered_set<uint64_t> s_generatedIDs; // To ensure uniqueness
    };
}

// Specialization of std::hash for FR::genID
namespace std {
    template <>
    struct hash<FR::genID> {
        std::size_t operator()(const FR::genID& val) const {
            return static_cast<std::size_t>(static_cast<uint64_t>(val));
        }
    };
}

#endif // FR_GENID_H