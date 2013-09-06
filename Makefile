all: run
run: compile
	./mesh.out
compile:
	g++ -Wall *.cpp -framework OpenGL -framework GLUT -o mesh.out
clean:
	rm mesh.out *.o
