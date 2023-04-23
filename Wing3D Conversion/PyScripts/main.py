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
import convertorERL
import convertorHRL
from enum import Enum
import ntpath

def pathOfFile(path):
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)

class fileType(Enum):
    HRLfile = 0
    ERLfile = 1
    notDefined = 2

Wings3DSrc='e:/TEMP/wings_08/e3d/'
Wings3DCppSrc = "e:/TEMP/PROJECT_CONVERT3D/"

def detectFileType(fn):
    """Detect file type based on filename
    Args:
        fn (function): Target file name 
    Raises:
        Exception: If file is not accessible
    Returns:
        _type_: two results, first is file type (HRL OR ERL), 
                             second is the new file name with 
                             cpp extension 
    """
    result=fileType.notDefined
    wfile = ""
    oFile=None
    ext = os.path.splitext(fn)[1]
    fname = pathOfFile(os.path.splitext(fn)[0])

    if not os.access((Wings3DSrc+fn), os.R_OK):
        print ("Failure opening file: No read access for %s" % fn)
        return result
    try:                                                                                                                                                      
        oFile = io.open((Wings3DSrc+fn), mode="r", encoding="utf-8")
        print ("Success opening file")
        oFile.close()
    except IOError:
        print ("Failed to access the file")
        return result, ""
    
    if (ext == ".hrl"):
        wfile=fname+".h"
        result=fileType.HRLfile
    else:
        wfile=fname+".cpp"
        result=fileType.ERLfile
    if(wfile==""):
        raise Exception("bad file name",fn)
    return (result,wfile)

def getAllFiles():
    allFiles=[]
    for entry in os.listdir(Wings3DSrc):
        if os.path.isfile(os.path.join(Wings3DSrc, entry)):
            #skips files that are not .erl or .hrl
            if (os.path.splitext(entry)[1]==".hrl" or os.path.splitext(entry)[1]==".erl" ):
                allFiles.append(entry)
    return allFiles
                
def main():
    #convertorERL.convertAFileERL("E:\\TEMP\\wings_08\\src\\wings.erl","E:\\TEMP\\wings_08\\src\\wings.cpp")
    #return
    currentFile=fileType.notDefined
    print("convert files")
    allFiles=getAllFiles()
    fWriteName=""

    for file in allFiles:
        currentFile,fWriteName=detectFileType(file)
        if currentFile==fileType.ERLfile:
            convertorERL.convertAFileERL((Wings3DSrc+file),((Wings3DCppSrc+fWriteName)))
        elif currentFile==fileType.HRLfile:
            convertorHRL.convertAFileHRL((Wings3DSrc+file),((Wings3DCppSrc+fWriteName)))
        else:
            print("Error, filename is wrong or not accessible ",file)

if __name__ == "__main__":
    main()
    