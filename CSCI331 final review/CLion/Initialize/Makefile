
all: test Load SSet
Load: BulkLoad.cpp Block.o
	g++ -o load.exe BulkLoad.cpp Block.o
SSet: blockwritetest.cpp Block.o
	g++ -o SSet blockwritetest.cpp Block.o -std=c++11
test: test.cpp fileOperations.h Block.o
	g++ Block.o test.cpp -std=c++11 -o test
Block.o:Block.cpp Block.h
	g++ -c Block.cpp -std=c++11
