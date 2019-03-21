all: test	

test: PA03.cpp FlightMap.v1.cpp FlightMap.v2.cpp
	g++ -c FlightMap.v1.cpp
	g++ -c FlightMap.v2.cpp
	g++ PA03.cpp FlightMap.v1.o FlightMap.v2.o -o test

clean:
	rm -rf *.o *.*~ test*