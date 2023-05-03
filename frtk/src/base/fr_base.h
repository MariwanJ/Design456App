//                                                                      
// This file is a part of the Open Source Design456App                    
// MIT License
// 
// Copyright (c) 2023
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
#include<frtk.h>
#include<Fr_Core.h>
class VERT {
public:
    float x, y, z;
};
class EDGE {
public:
    VERT point[2];
};
/** Wire must be sequential edges. */
class WIRE {
public:
    std::vector<std::shared_ptr<EDGE>> edge;
    bool closed;

    /** Functions */
public:
    bool operator==(const WIRE& w1) const;
    std::shared_ptr<EDGE> getEdge(unsigned int val);
    std::shared_ptr<EDGE> insert(unsigned int val,std::shared_ptr<EDGE>edg);
private:
    bool checkValid();//Return false if edges are not sequential
};

class FACE{
public:
    std::vector < std::shared_ptr<WIRE>> wire;
private:
    bool checkValid(); //Check if the wires are closed otherwise it fails.
};

class we{
public:
    std::unordered_map<FACE, std::string> 
};
