app: Point.o Centroid.o myVector.o PointReader.o kMeansCalc.o main*.o
	g++ main*.o -o app

Point.o: ./lib/Point.cpp
	g++ -c ./lib/Point.cpp
Centroid.o: ./lib/Centroid.cpp
	g++ -c ./lib/Centroid.cpp
myVector.o: ./lib/myVector.cpp
	g++ -c ./lib/myVector.cpp
PointReader.o: ./lib/PointReader.cpp
	g++ -c ./lib/PointReader.cpp
kMeansCalc.o: ./lib/kMeansCalc.cpp
	g++ -c ./lib/kMeansCalc.cpp

clean:
	rm *.o app
