all: build graph.a view.o controller.o main.o
	cc -o lab5 build/*.o -lreadline -L./build -lgraph -std=c11 -g

build:
	mkdir build

graph.a: Graph.o
	ar rcs build/libgraph.a build/Graph.o
	rm build/Graph.o

main.o:
	cc -c main.c -o build/main.o -std=c11 -g

view.o:
	cc -c view/view.c -o build/view.o -std=c11 -g

controller.o:
	cc -c controller/controller.c -o build/controller.o -std=c11 -g

Graph.o:
	cc -c model/Graph.c -o build/Graph.o -std=c11 -g

clean:
	rm -rf build/
	rm lab5