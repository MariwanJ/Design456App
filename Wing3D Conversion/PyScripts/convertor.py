import sys,os
import io

basepath = 'e:/TEMP/wings_08/src'
convertedpath = "e:/TEMP/PROJECT_CONVERT3D/"

def getAllFailes():
    allFiles=[]
    for entry in os.listdir(basepath):
        if os.path.isfile(os.path.join(basepath, entry)):
            if (os.path.splitext(entry)[1]==".hrl" or os.path.splitext(entry)[1]==".erl" ):
                allFiles.append(entry)

def convertAFile(fn):
    if not os.access(fn, os.R_OK):
        print ("Failure opening file: No read access for %s" % fn)
        return
    
    try:                                                                                                                                                      
        ofile = io.open(fn, mode="r", encoding="utf-8")
        print ("Success opening file")
    except IOError:
        print ("Failed to access the file")
        return
    
    ext = os.path.splitext(fn)[1]
    fname = os.path.splitext(fn)[0]
    wfile = ""
    if (ext == ".hrl"):
        wfile=fname+".h"
    else:
        wfile=fname+".cpp"
    if(wfile==""):
        raise Exception("bad file name",fn)
    

    
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
        if (line[:2]=="%%"):
            #skip comments
            line=line.replace("%%", "//",2)
            answer.append(line)
        elif (line.find("-ifdef")!=-1):
                answer.append("#ifdef ")
                line=line.replace("-ifdef","",1)
                line=line.replace(".","")
                answer.append(line)
                answer.append(" ")

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


        elif (line.find("-endif.")!=-1):
            answer.append("#endif")

        elif(line.find("-define")!=-1):
            answer.append("#define ")
            line=line.replace("-define","",1)
            line=line.replace("("," ",1) #only once
            line=line.replace(")"," ",1) #only once
            line=line.replace(","," ",1) #only once
            line=line.replace(".","")
            answer.append(line)

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
     
        
def convertAll(files):
    for fn in files:
        convertAFile(fn)
        



def main():
    print("convert files")
    convertAFile("e:\\TEMP\\wings_08\\src\\wings.hrl")

if __name__ == "__main__":

    main()
    