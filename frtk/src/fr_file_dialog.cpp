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
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//
#include <fr_file_dialog.h>
namespace FR {
    fileDialog::fileDialog(std::string path,
        std::vector<std::string> filter,
        std::string title) :m_filters(filter),
        m_defaultpath(path), m_title(title)
    {
    }
    void fileDialog::filter(std::vector<std::string>& filter)
    {
        m_filters = filter;
    }
    std::vector<std::string>& fileDialog::filter()
    {
        return m_filters;
    }
    std::string fileDialog::openFile() {
        const char** filters = new const char* [m_filters.size()];
        for (size_t i = 0; i < m_filters.size(); ++i) {
            filters[i] = m_filters[i].c_str();
        }
        
            const char* result = tinyfd_openFileDialog(
            m_title.c_str(),          // Dialog title
            m_defaultpath.c_str(),    // Default path
            m_filters.size(),         // Number of filter patterns
            filters,                  // Filter patterns
            NULL,                    // Filter description
            0                        // Allow multiple selection?
        );
        if (result) {
            return std::string(result); 
        }
        else {
            return ""; // or handle cancel case differently
        }
    }
    std::string fileDialog::saveFile(std::string fileName) {
        const char** filters = new const char* [m_filters.size()];
        for (size_t i = 0; i < m_filters.size(); ++i) {
            filters[i] = m_filters[i].c_str();
        }
        const char* result = tinyfd_saveFileDialog(
            m_title.c_str(),          // Dialog title
            fileName.c_str(),        // Default filename
            m_filters.size(),        // Number of filter patterns
            filters,                 // Filter patterns
            NULL                    // Filter description
        );
        if (result) {
            return std::string(result);
        }
        else {
            return ""; // or handle cancel case differently
        }
    }
}