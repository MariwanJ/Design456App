O = o
CC = gcc
LINK = gcc

OBJ = Attrib.$(O) create.$(O) data.$(O) CrIFrBuf.$(O) hashtab.$(O) Image.$(O) Info.$(O) misc.$(O) parse.$(O) RdFToI.$(O) rgb.$(O) simx.$(O)
CFLAGS = -g -O2 -I../include/X11 -I. -DFOR_MSW
EMPTY=
SPACE = $(EMPTY) $(EMPTY)
LINK_DLL = -shared
LINK_FLAGS =
LINK_OUT = -o$(SPACE)
DLL_EXPORTS = libXpm.def
LIBS = -lgdi32 -lcrtdll

all: libXpm.dll

libXpm.dll: $(OBJ)
	$(LINK) $(LINK_DLL) $(LINK_OUT)$@ $(LINK_FLAGS) $(DLL_EXPORTS) $(OBJ) $(LIBS)
