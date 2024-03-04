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
//Inspired by Hazel engine

#ifndef FR_COMPONENTS_H
#define FR_COMPONENTS_H
#include<fr_genID.h>
namespace FR {

    class test {
    public:
        // Default constructor
        test() {
            ttt = std::make_shared<std::string>("testme \n");
        }

        // Copy constructor
        test(const test& other) {
            // Perform a deep copy of the shared_ptr content
            if (other.ttt) {
                ttt = std::make_shared<std::string>(*other.ttt);
            }
        }

        // Move constructor
        test(test&& other) noexcept {
            // Move the shared_ptr content
            ttt = std::move(other.ttt);
            // Set the source shared_ptr to null to avoid double deletion
            other.ttt = nullptr;
        }

        // Move assignment operator
        test& operator=(test&& other) noexcept {
            if (this != &other) {
                // Release the current shared_ptr content
                ttt = nullptr;

                // Move the shared_ptr content
                ttt = std::move(other.ttt);

                // Set the source shared_ptr to null to avoid double deletion
                other.ttt = nullptr;
            }
            return *this;
        }

        // Destructor
        ~test() {
            std::cout << "end of project";
        }

        void printme() {
            if (ttt) {
                std::cout << *ttt << std::endl;
                return;
            }
        }

    private:
        std::shared_ptr<std::string> ttt;
    };



	class FRTK_API ItemID
	{
	public:
		ItemID() = default;
		ItemID(const ItemID&) = default;
		genID ID;
	};

	class FRTK_API ItemName
	{
	public:

		ItemName() = default;
		ItemName(const ItemName&) = default;
		ItemName(const std::string& name): m_Name(name) {}
		std::string m_Name;

	};

}
#endif
