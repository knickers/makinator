all:
	g++ -o printer -lglut -lGLU main.cpp shapes.cpp slider.cpp colors.cpp printer.cpp save.cpp
	./printer

