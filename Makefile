all: run
run: compile
	./mesh.out
compile:
	clang -x c++ *.cpp -framework OpenGL -framework GLUT -l stdc++ -o mesh.out
clean:
	rm mesh.out *.o
