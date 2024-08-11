STD=--std=c++17
GCC=g++
BIN=bin
OBJ=obj

bin/typer: src/main.cpp obj/test.o obj/checker.o
	[ -d $(BIN) ] || mkdir -p $(BIN)
	${GCC} ${STD} -o bin/poker src/main.cpp obj/test.o obj/checker.o

obj/test.o: src/test.h src/test.cpp obj/checker.o src/colors.h
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/test.o src/test.cpp

obj/checker.o: src/checker.h src/checker.cpp
	[ -d $(OBJ) ] || mkdir -p $(OBJ)
	${GCC} ${STD} -c -o obj/checker.o src/checker.cpp

run: bin/poker
	bin/poker

.PHONY: doc
doc:
	doxygen config
	cd latex && make

clean:
	rm -f bin/*
	rm -rf bin
	rm -r -f result/*