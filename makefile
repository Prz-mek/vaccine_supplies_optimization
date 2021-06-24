CC = g++
COPT = -pedantic -Wall

build/voco: src/main.cpp build/solver.o build/reader.o build/network.o build/arraylist.o build/redblacktree.o
	$(CC) $(COPT) -o build/voco src/main.cpp build/solver.o build/reader.o build/network.o build/arraylist.o build/redblacktree.o

build/solver.o: src/solver.hpp src/solver.cpp
	$(CC) $(COPT) -o build/solver.o -c  src/solver.cpp

build/reader.o: src/reader.hpp src/reader.cpp
	$(CC) $(COPT) -o build/reader.o -c  src/reader.cpp

build/network.o: src/network.hpp src/network.cpp
	$(CC) $(COPT) -o build/network.o -c  src/network.cpp

build/arraylist.o: src/arraylist.hpp src/arraylist.cpp
	$(CC) $(COPT) -o build/arraylist.o -c  src/arraylist.cpp

build/redblacktree.o: src/redblacktree.hpp src/redblacktree.cpp
	$(CC) $(COPT) -o build/redblacktree.o -c  src/redblacktree.cpp

.PHONY: clean tests run_tests input_test gen

clean:
	-rm build/*.o
	-rm build/voco
	-rm build/test/*

gen: test/generator.cpp
	$(CC) $(COPT) -o build/test/generator.cpp test/generator.cpp

tests:
	$(CC) $(COPT) -o build/test/arraylist_test test/arraylist_test.cpp src/arraylist.cpp src/network.cpp
	$(CC) $(COPT) -o build/test/redblacktree_test test/redblacktree_test.cpp src/redblacktree.cpp
	$(CC) $(COPT) -o build/test/network_test test/network_test.cpp src/network.cpp
	$(CC) $(COPT) -o build/test/solver_test test/solver_test.cpp src/network.cpp src/solver.cpp src/arraylist.cpp

run_tests:
	./build/test/arraylist_test
	./build/test/redblacktree_test
	./build/test/network_test
	./build/test/solver_test

input_test: build/voco
	./build/voco -i test_data/bad_data1.txt
	./build/voco -i test_data/bad_data2.txt
	./build/voco -i test_data/bad_data3.txt
	./build/voco -i test_data/bad_data4.txt
	./build/voco -i test_data/bad_data5.txt
	./build/voco -i test_data/bad_data6.txt
	./build/voco -i test_data/bad_data7.txt
