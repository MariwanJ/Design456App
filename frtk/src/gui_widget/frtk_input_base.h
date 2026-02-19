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

#ifndef  FRTK_INPUT_BASE_H
#define  FRTK_INPUT_BASE_H

#include <frtk.h>
#include <gui_widget/frtk_box.h>
#include <gui_widget/frtk_draw.h>


namespace FR {
    struct TextInput {
        std::string value; //float, double, int & string values: Everything will be string, easier to edit. 
        size_t cursorPos; 
        size_t selStart;  
      //  int selEnd;    
    };

    class Frtk_Input_Base : public Frtk_Box {
    public:
        Frtk_Input_Base(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b = FRTK_FLAT_BOX);

        std::string cpToUTF8(uint32_t cp);

        void value(int value);
        void value(float value);
        void value(double value);
        void value(const char* value);
        void value(std::string& value);
        int ivalue() const;
        double dvalue() const;
        int size() const;

        int mark(int markIndex);

        int insert_position(int p, int m);
        int replace(int beg, int end, const char* text, int ilen = 0);

        int cut(int n);
        int cut(int beg, int end);

        int insert(const char* t, int length);

        int copy();
        int paste();

        int undo();
        bool can_undo() const;
        int redo();

        bool readonly() const;
        void readonly(bool val);
        int wrap() const;
        void wratp(int b);


        //Type checks
        bool isEditable() const;
        bool isSelectable() const;
        bool isWrapped() const;
        bool isSingleLine() const;
        bool isSecret() const;

    protected:
        virtual int handle(int ev) override;
        void drawEditBoxBase(float x, float y, float w, float h);
        virtual void draw() override;
        virtual void draw_cursor();

        int word_start(int ind) const;
        int word_end(int ind) const;
        int line_strart(int ind) const;
        int line_end(int ind) const;

        bool delSel();

        TextInput m_text;
        int m_tab_nav;

    private:

        bool isInteger(const std::string& str, int& value) {
            auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
            return ec == std::errc() && ptr == str.data() + str.size();
        }

        bool isFloat(const std::string& str, float& value) {
            char* endptr = nullptr;
            value = std::strtof(str.c_str(), &endptr);
            return endptr == str.c_str() + str.size();
        }

        bool isDouble(const std::string& str, double& value) {
            char* endptr = nullptr;
            value = std::strtod(str.c_str(), &endptr);
            return endptr == str.c_str() + str.size();
        }

    };
}
#endif // ! FRTK_SEARCH_BOX_H
