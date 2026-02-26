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
#include <nanovg.h>

namespace FR {
    struct TextInput {
        std::string value; //float, double, int & string values: Everything will be string, easier to edit. 
        size_t cursorPos; 
        size_t selStart;  
      //  int selEnd;    
    };

    class FRTK_API  Frtk_Input_Base : public Frtk_Box {
    public:
        Frtk_Input_Base(NVGcontext* vg, float X, float Y, float W, float H, std::string lbl, BOX_TYPE b = FRTK_DOWN_BOX);
        
        std::string cpToUTF8(uint32_t cp);

        void value(int value);
        void value(float value);
        void value(double value);
        void value(const char* value);
        void value(const std::string& v);

        int ivalue() const;
        float fvalue() const; 
        double dvalue() const;
        int size() const;

        void draw_selection();

        int mark(int markIndex);

        int insert_positionn(int p, const char* t, int length) ;
        int insert_positionn(int p, std::string & t);
        int replace(int beg, int end, const char* text, int ilen = 0);

        int cut(int n);
        int cut(int beg, int end);

        int insert(const char* t, int length);

        int insert(const std::string& t);

        int copy();
        int paste();

        int undo();
        bool can_undo() const;
        int redo();

        bool readonly() const;

        int wrap() const;
        void wratp(int b);


        //Type checks
        bool isEditable() const;
        bool isSelectable() const;
        bool isWrapped() const;
        bool isSingleLine() const;
        bool isSecret() const;

        virtual void lose_focus() override;
        
        
    protected:
        // Return true if character or string is allowed
        virtual bool validateChar(char c) const;
        virtual bool validateString(const std::string& s) const;

        virtual int handle(int ev) override;
        void drawEditBoxBase(float x, float y, float w, float h);
        virtual void draw() override;
        virtual void draw_cursor();

        int mouseXToCharIndex();

        int word_start(int ind) const;
        int word_end(int ind) const;
        int line_strart(int ind) const;
        int line_end(int ind) const;

        bool delSel();

        TextInput m_text;
        int m_tab_nav;

    private:
        NVGcolor m_cursorColor;
        inline bool isInteger(const std::string& str, int& value) {
            auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), value);
            return ec == std::errc() && ptr == str.data() + str.size();
        }

        inline bool isFloat(const std::string& str, float& value) {
            char* endptr = nullptr;
            value = std::strtof(str.c_str(), &endptr);
            return endptr == str.c_str() + str.size();
        }

        inline bool isDouble(const std::string& str, double& value) {
            char* endptr = nullptr;
            value = std::strtod(str.c_str(), &endptr);
            return endptr == str.c_str() + str.size();
        }


        inline bool isSoftValidFloat(const std::string& s)
        {
            if (s.empty()) return true;
            if (s == "-" || s == "." || s == "-.") return true;
            bool hasDot = false;
            size_t i = (s[0] == '-') ? 1 : 0;
            for (; i < s.size(); ++i)
            {
                if (std::isdigit((unsigned char)s[i]))
                    continue;
                if (s[i] == '.' && !hasDot)
                {
                    hasDot = true;
                    continue;
                }
                return false;
            }
            return true;
        }
        inline bool isSoftValidDouble(const std::string& s)
        {
            if (s.empty()) return true;
            if (s == "-" || s == "." || s == "-.") return true;
            bool hasDot = false;
            bool hasExp = false;
            size_t i = (s[0] == '-') ? 1 : 0;
            for (; i < s.size(); ++i)
            {
                char c = s[i];
                if (std::isdigit((unsigned char)c))
                    continue;
                if (c == '.' && !hasDot && !hasExp)
                {
                    hasDot = true;
                    continue;
                }
                if ((c == 'e' || c == 'E') && !hasExp)
                {
                    hasExp = true;
                    continue;
                }
                if ((c == '-' || c == '+') && i > 0 &&
                    (s[i - 1] == 'e' || s[i - 1] == 'E'))
                    continue;
                return false;
            }
            return true;
        }
        inline bool isSoftValidInt(const std::string& s)
        {
            if (s.empty()) return true;
            if (s == "-") return true;
            size_t i = (s[0] == '-') ? 1 : 0;
            for (; i < s.size(); ++i)
                if (!std::isdigit((unsigned char)s[i]))
                    return false;
            return true;
        }
    };
}
#endif // FRTK_INPUT_BASE_H
