# The name of the executable to produce
EXE = Menu.exe
# The objects to link
OBJS = menu.o draw.o

# Get the name of the platform
SYS = $(shell uname)
# If it's on a mac do sdl-config
ifneq (, $(findstring Darwin, $(SYS)))
LIBS = $(shell sdl-config --static-libs --cflags)
else
# If we're on windows, then set the libs manually
LIBS = -lmingw32 -lSDLmain -lSDL -lopengl32
endif

# Link the full application
$(EXE) : $(OBJS)
	g++ -o $(EXE) $(OBJS) $(LIBS)

# Compile all .cpps into .os
%.o : %.cpp
	g++ $< -c
