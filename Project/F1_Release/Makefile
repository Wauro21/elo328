DEPENDENCIES = polyfit.h LaneDetection.h Projection.h racingLine.h segFunctions.h Matrix.h mapGeneration.h

DEPCPP = LaneDetection.cpp Projection.cpp racingLine.cpp segFunctions.cpp Matrix.cpp mapGeneration.cpp

OPENCV = `pkg-config --cflags --libs opencv4`
PYTHON = -I/usr/include/python3.6 -lpython3.6m
FLAGS = -Wall -Wextra

INPUT = main.cpp
OUTPUT = F1_Release

default: build


build: $(DEPENDENCIES) $(DEPCPP)
	g++ $(FLAGS) -o $(OUTPUT) $(INPUT) $(DEPCPP) $(OPENCV) $(PYTHON)

clean: $(OUTPUT)
	rm $(OUTPUT)
	rm *.png
