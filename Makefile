CC = g++

# make the randmst.cpp file and output it as randmst.cpp
randmst: randmst.cpp
	$(CC) -o randmst.o randmst.cpp Graph.cpp UnionFind.cpp -lm

tests: tests.cpp
	$(CC) -ggdb3 -O3 -std=c++11 -o tests.o tests.cpp Graph.cpp UnionFind.cpp 
x:
	-lm -pthread -ltbb

parallel: randmst.cpp
	$(CC) -ggdb3 -O3 -std=c++11 -o randmst.o randmst.cpp Graph.cpp UnionFind.cpp -lm -pthread -ltbb
