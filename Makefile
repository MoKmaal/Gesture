Gesture: Gmain.o Gdata.o Gsetup.o
	g++ Gmain.o Gdata.o Gsetup.o -o Gesture
Gmain.o: Gmain.cpp
	 g++ -c Gmain.cpp
Gdata.o: Gdata.cpp
	 g++ -c Gdata.cpp
Gsetup.o: Gsetup.cpp
	 g++ -c Gsetup.cpp
clean:
	rm *.o Gesture 
