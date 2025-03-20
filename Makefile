all: sum-nbo

sum-nbo: main.o nbo.o
	g++ -o sum-nbo main.o nbo.o

main.o: nbo.h main.cpp
	g++ -c -o main.o main.cpp

nbo.o: nbo.h nbo.cpp
	g++ -c -o nbo.o nbo.cpp

clean:
	rm -f sum-nbo
	rm -f *.o
