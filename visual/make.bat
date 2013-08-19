g++ -ggdb main.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -o main.o

g++  -o a.exe main.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lopengl32 -lglu32
