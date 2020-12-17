OUTPUT = TEST
INPUT  = main.cpp
DEPENDENCIES = Matrix.cpp mapGeneration.cpp
default: build

build:
	g++ -Wall -Wextra -o $(OUTPUT) $(INPUT) $(DEPENDENCIES) -I/usr/include/python3.6 -lpython3.6m

clean:
	rm $(OUTPUT)
