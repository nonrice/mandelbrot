.PHONY: run

run: ./bin/mandelbrot
	./bin/mandelbrot

./bin/mandelbrot: src/main.cpp src/mandelbrot.cpp include/tinycolormap.hpp include/mandelbrot.hpp
	mkdir -p ./bin
	clang++ src/main.cpp src/mandelbrot.cpp -o bin/mandelbrot -std=c++17 -Ofast -Wall -Wextra -I./include $(shell pkg-config --cflags --libs sdl2) 
