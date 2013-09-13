CC=clang
CFLAGS=-x c++ -l stdc++ -Wc++11-extensions
EXECUTABLE=mesh.out

all: run
run: compile
	./$(EXECUTABLE)
compile:
	$(CC) $(CFLAGS) *.cpp -framework OpenGL -framework GLUT -o $(EXECUTABLE)
clean:
	rm *.o $(EXECUTABLE)
