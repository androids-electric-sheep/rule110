all:
	clang-format -i main.cpp
	g++ -g -std=c++14 main.cpp
clean:
	rm -f a.out
