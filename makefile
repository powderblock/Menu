menu.exe : menu.cpp
	g++ menu.cpp draw.cpp -o menu.exe -lmingw32 -lSDLmain -lSDL -lopengl32