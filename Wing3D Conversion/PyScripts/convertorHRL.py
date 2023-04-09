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
                answer.append("#ifdef ")
                line=line.replace("-ifdef","",1)
                line=line.replace(".","")
                answer.append(line)
                answer.append(" ")
        #-include_lib
        elif (line.find("-include_lib")!=-1):
            line=line.replace ('\n', " ")
            line=line.replace ('-', " ")
            line=line.replace ('.', " ")
            line=line.replace ('(', " ")
            line=line.replace (')', " ")
        
            answer.append("\n#include ")
            line=line.replace(".hrl",".h",1)
            line=line.replace ("include_lib","",1)
            answer.append(line)
        
                
        #-include(xxxx)
        elif (line.find("-include")!=-1):
            line=line.replace ('\n', " ")
            line=line.replace ('-', " ")
            line=line.replace ('.', " ")
            line=line.replace ('(', " ")
            line=line.replace (')', " ")
                 
            answer.append("\n#include ")
            line=line.replace(".hrl",".h",1)
            line=line.replace ("include_lib","",1)
            answer.append(line)

        #-endif. 
        elif (line.find("-endif.")!=-1):
            answer.append("#endif")
        
        #-define
        elif(line.find("-define")!=-1):
            answer.append("#define ")
            line=line.replace("-define","",1)
            line=line.replace("("," ",1) #only once
            line=line.replace(")"," ",1) #only once
            line=line.replace(","," ",1) #only once
            line=line.replace(".","")
            line=line.replace("bor","|")
            line=line.replace("bnot", "~")       
            answer.append(line)
           
        #-record
        elif(line.find("-record")!=-1):
            line=line.replace("-record","",1 )
            line=line.replace("(","",1) #record end
            line=line.replace(",","",1) #record end
            line=line.replace("\n","")
            answer.append("\nstruct ")
            answer.append(line)
            answer.append(" {\n")
            
            i=i+1
            while(Lines[i].find("}).")==-1):
                #record which is a struct definition
                line=Lines[i]
                line=line.replace("%", "//")
                line=line.replace("{", " ")
                line=line.replace("}", " ")
                line=line.replace("(","",1) #record end
                line=line.replace(",",";",1)
                answer.append("auto ")
                answer.append(line)
                i=i+1
            answer.append("};\n")
        
        answers.append(answer)
    
    for ans in answers:
        wfileOpen.write(''.join(ans))
    wfileOpen.close()
     
        
