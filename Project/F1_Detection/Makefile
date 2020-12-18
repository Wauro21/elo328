main: main.cpp polyfit.h LaneDetection.h Projection.h racingLine.h segFunctions.h
	g++ -o test main.cpp LaneDetection.cpp Projection.cpp racingLine.cpp segFunctions.cpp `pkg-config --cflags --libs opencv4`
	
clean:
	rm *.png
	rm test
