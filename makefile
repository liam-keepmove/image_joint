.PHONY: all stitch perspective

all:
	g++ -std=c++17 test.cpp -o test.out `pkg-config --cflags --libs opencv4 fmt libzmq`

stitch:
	g++ -std=c++17 stitch.cpp -o stitch.out `pkg-config --cflags --libs opencv4 fmt libzmq`

perspective:
	g++ -std=c++17 perspective.cpp -o perspective.out `pkg-config --cflags --libs opencv4 fmt libzmq`
