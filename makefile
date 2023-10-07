output: driver.cpp Licorice.o
	g++ driver.cpp Licorice.o -o output

Licorice.o: Licorice.cpp
	g++ -c Licorice.cpp

clean:
	rm *.o output
