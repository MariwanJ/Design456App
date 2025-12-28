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
// Inspired by Hazel engine
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#include "fr_genID.h"
#include <random>
#include <unordered_set>

// Static member initialization
namespace FR {
    std::random_device genID::s_r_mDevice;
    std::mt19937_64 genID::s_Engine(s_r_mDevice());
    std::uniform_int_distribution<uint64_t> genID::s_udf(0, UINT64_MAX);
    std::unordered_set<uint64_t> genID::s_generatedIDs;

    // Default constructor
    genID::genID() : m_genID(generate()) {}

    // Constructor with specific ID
    genID::genID(uint64_t u) : m_genID(u) {
        // Ensure the specific ID is unique
        if (!s_generatedIDs.insert(u).second) {
            throw std::invalid_argument("ID must be unique");
        }
    }

    // Generate a new unique ID
    uint64_t genID::generate() {
        uint64_t newID;

        // Ensure uniqueness
        do {
            newID = s_udf(s_Engine);
        } while (!s_generatedIDs.insert(newID).second); // Retry until a unique ID is found

        return newID;
    }
}