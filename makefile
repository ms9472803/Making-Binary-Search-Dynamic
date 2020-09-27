main:main.o DynamicBS.o
	g++ -o a.exe main.o DynamicBS.o

main.o:main.cpp DynamicBS.h 
	g++ -c main.cpp

DynamicBS.o:DynamicBS.cpp DynamicBS.h 
	g++ -c DynamicBS.cpp

clean:
	del /Q /F a.exe *.o