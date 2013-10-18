CC=clang
CFLAGS=-x c++ -l stdc++ -Wc++11-extensions
EXECUTABLE="OBJ Viewer"
OBJ=fixtures/cube.obj

all: run
run: compile
	./$(EXECUTABLE) $(OBJ)
compile:
	$(CC) $(CFLAGS) *.cpp -framework OpenGL -framework GLUT -o $(EXECUTABLE)
clean:
	rm *.o $(EXECUTABLE)
