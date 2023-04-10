
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

def convertIncludeLib(Lines,i):
    nAnswers=[]
    line=Lines[i]
    line=line.replace ('\n', " ")
    line=line.replace ('-', " ")
    line=line.replace ('.', " ")
    line=line.replace ('(', " ")
    line=line.replace (')', " ")
    nAnswers.append("\n#include ")
    line=line.replace(".hrl",".h",1)
    line=line.replace ("include_lib","",1)
    nAnswers.append(line)
    return (nAnswers,i)
    
def convertRecord(Lines,i):
    nAnswer=[i]
    line=line.replace("-record","",1 )
    line=line.replace("(","",1) #record end
    line=line.replace(",","",1) #record end
    line=line.replace("\n","")
    nAnswer.append("\nstruct ")
    nAnswer.append(line)
    nAnswer.append(" {\n")
    
    i=i+1
    while(Lines[i].find("}).")==-1):
        #record which is a struct definition
        line=Lines[i]
        line=line.replace("%", "//")
        line=line.replace("{", " ")
        line=line.replace("}", " ")
        line=line.replace("(","",1) #record end
        line=line.replace(",",";",1)
        nAnswer.append("auto ")
        nAnswer.append(line)
        i=i+1
    nAnswer.append("};\n")
    return(nAnswer,i)
            
def convertInclude(Lines,i):
    nAnswers=[]
    line=Lines[i]
    line=line.replace ('\n', " ")
    line=line.replace ('-', " ")
    line=line.replace ('.', " ")
    line=line.replace ('(', " ")
    line=line.replace (')', " ")
            
    nAnswers.append("\n#include ")
    line=line.replace(".hrl",".h",1)
    line=line.replace ("-include","",1)
    nAnswers.append(line)
    nAnswers.append("\n")
    return (nAnswers,i)
            
def convertDefine(Lines,i):
    line=Lines[i]
    nAnswers=[]
    nAnswers.append("#define ")
    line=line.replace("-define","",1)
    line=line.replace("("," ",1) #only once
    line=line.replace(")"," ",1) #only once
    line=line.replace(","," ",1) #only once
    line=line.replace(".","")
    nAnswers.append(line)
    return (nAnswers,i)


def convertImport(Lines,i):
    nAnswers=[]
    line=Lines[i]
    line=line.replace ('\n', " ")
    line=line.replace ('-', " ")
    line=line.replace ('.', " ")
    line=line.replace ('(', " ")
    line=line.replace (')', " ")
    line=line.replace ('-import', "")
    nAnswers.append("\n#include ")
    nAnswers.append(line.split()[0])
    nAnswers.append("//")  #just to make it clear
    nAnswers.append(line)
    return (nAnswers,i)

def convertIfDef(Lines,i):
    nAnswers=[]
    line=Lines[i]
    nAnswers.append("#ifdef ")
    line=line.replace("-ifdef","",1)
    line=line.replace(".","")
    nAnswers.append(line)
    nAnswers.append(" ")
    return (nAnswers,i)


            
def convertFunction(Lines,i):
    line=Lines[i]
    nAnswers=[]
    nAnswers.append("\nvoid ") #all functions will be void for simplicity
    line=line.replace("->","",1)
    line=line.replace("%","//")
    nAnswers.append(line.split()) #function name  
    nAnswers.append("{")  
    nAnswers.append("\n")
    i=i+1
    line=Lines[i]
    while (line.find( ";")==-1 and line.find( ".")==-1):
        line=line.replace("%","//")
        line=line.replace("end).","",1)
        line=line.replace("of","")
        line=line.replace("ok","",1)
        line=line.replace ("ok -> ok","",1)
        if(line.find("case")!=-1):
            nAnswers.append("\nswitch(")
            nAnswers.append(line)
            nAnswers.append(") {\n")
            nAnswers.append("case "),
            nAnswers.append(line.split()[0])
        nAnswers.append(line)
        i=i+1
        line=Lines[i]
    line=line.replace("end).","",1) 
    line=line.replace("end.","",1)    
    nAnswers.append(line)                 
    nAnswers.append("}")
    return (nAnswers,i)