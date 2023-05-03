#include "fr_genID.h"
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
unsigned int genID::lastID=0; //This is a sequential 
unsigned int genID::usedSize=0; //No of use ID:s

genID::genID()
{
	used.reserve(SEGMENT_SIZE); //At the beginning
    for (int i = 0; i < 100; i++) {
		used[i] = false;
	}
}

unsigned int genID::getID()
{
	if (usedSize < used.size()) {
		//We have fragmantation. search for not used id
		unsigned int x = 0;
		while (used[x] != false) {
			x++;
			if (x >= (used.size() - 1))
				break; //not found all is used. Here we have a problem. 
		}
		if (used[x] == false) {
			used[x] = true;
			usedSize++;
			return x;
		}
	}
	if (lastID >= (used.size()-1)) {		//should never be grater but just in case
		//resize and create new item we reached the last item
		used.resize(used.size() + SEGMENT_SIZE);//add 1k values
		for (int i = used.size(); i < (used.size() + SEGMENT_SIZE);i++) {
			used[i] = false;
		}
		used[lastID] = true;
		lastID++;
		usedSize++;
		return (lastID-1);
	}
	else {
		//This should work if other conditions fails
		used[lastID] = true;
		usedSize++;
		lastID++;
		return(lastID - 1);
	}
}

bool genID::isUsed(unsigned int id)
{
	return used[id]; //True if it is used, false if it is not used by any object
}

void genID::freeID(unsigned int id)
{
	if (id > used.size()) {
		throw ("ID not found");
		return;
	}
	usedSize--; //always decrease 
	if (id== lastID){
		lastID--;
	}
	else {
		/*We cannot change lastID since the removed id is not the last item in the vector.
			This will cause fragmentation which genID should take care of it
		*/
		
		usedSize--;
	}
	used[id] = false;
}