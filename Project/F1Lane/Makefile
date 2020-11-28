NAME = TEST

default: build

build:
	g++ -o $(NAME) detection.cpp `pkg-config --cflags --libs opencv4`

clean: $(NAME)
	rm $(NAME)
