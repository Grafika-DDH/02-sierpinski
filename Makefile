cube:
	g++ cube.cpp -Llib-mingw/ -lopengl32 -lgdi32 .\glfw3.dll -o cube

triangle:
	g++ sierpinski.cpp -Llib-mingw/ -lopengl32 -lgdi32 .\glfw3.dll -o triangle

mainmenu:
	g++ mainmenu.cpp -Llib-mingw/ -lopengl32 -lgdi32 .\glfw3.dll -o mainmenu