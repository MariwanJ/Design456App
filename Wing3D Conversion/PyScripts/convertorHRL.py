#
# This file is a part of the Open Source Design456App
# Wings3D conversion interpreter to c/cpp
# MIT License
#
# Copyright (c) 2023
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
#  Author :Mariwan Jalal    mariwan.jalal@gmail.com
#

import sys,os
import io
from conversions import *

def convertAFileHRL(fn , wfile):
    isModule=False
    if not os.access(fn, os.R_OK):
        print ("Failure opening file: No read access for %s" % fn)
        return
    try:                                                                                                                                                      
        ofile = io.open(fn, mode="r", encoding="utf-8")
        print ("Success opening file")
    except IOError:
        print ("Failed to access the file")
        return
    
    wfileOpen=io.open(wfile, mode="w+", encoding="utf-8")
    answers=[]

    try:
        Lines=ofile.readlines()
    except Exception as e: #Should be replaceable with IOError, doesn't hurt to not 
        sys.stderr.write('%s\n' % e)
        sys.exit(1)
    i=0
    for i in range(0,len(Lines)): 
        line=Lines[i]
        answer=[]
        #comments %%
        if (line[:2]=="%%"):
            #skip comments
            line=line.replace("%%", "//",2)
            answer.append(line)
            
        #-module
        elif (line.find("-module")!=-1):
            answer.append("namespace {")
            isModule = True
        #-ifdef
        elif (line.find("-ifdef")!=-1):
            answer,i=convertIfDef(Lines,i)
            
        #-include_lib
        elif (line.find("-include_lib")!=-1):
            answer,i= convertIncludeLib(Lines,i)
                
        #-include(xxxx)
        elif (line.find("-include")!=-1):
            answer,i=convertInclude(Lines,i)

        #-endif. 
        elif (line.find("-endif.")!=-1):
            answer.append("#endif")
        
        #-define
        elif(line.find("-define")!=-1):
            answer,i= convertDefine(Lines,i)
           
        #-record
        elif(line.find("-record")!=-1):
            answer,i=convertRecord(Lines,i)
        
        answers.append(answer)
    
    for ans in answers:
        wfileOpen.write(''.join(ans))
    if (isModule is True):
        wfileOpen.write(''.join("}"))
    wfileOpen.close()
     
        
