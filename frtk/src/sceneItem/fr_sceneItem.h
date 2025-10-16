//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2025
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
#include <fr_genID.h>
#include <memory>
#include <string>

namespace FR {
    struct SceneItemStruct {
        std::shared_ptr<Fr_Widget> Sceneitem;
        uint64_t id;
        std::string name;
        //Default constructor
        SceneItemStruct(std::shared_ptr<Fr_Widget> item = nullptr,
            const std::string& itemName = "NoName",
            uint64_t itemId = genID())
            : Sceneitem(item),id(itemId), name(itemName) {
        }
        // Define operator== for comparing SceneItemStruct objects
        bool operator==(const SceneItemStruct& other) const {
            return (id == other.id );
        }
    };
}

#endif