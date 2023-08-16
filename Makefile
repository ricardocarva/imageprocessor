ALL = $(wildcard src/*.cpp)
MAIN = $(filter-out src/test.cpp, $(ALL))
TEST = $(filter-out src/main.cpp, $(ALL)) 

build:
	g++ -std=c++11 $(MAIN) -o project2.out

test:
	g++ -std=c++11 $(TEST) -o project2.out

run:
	./project2.out

clean:
	rm *.out
	rm ./output/*.tga

