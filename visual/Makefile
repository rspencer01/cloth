CPP=g++
FLAGS = -g
obj = main.o
lib = -lglut -lGLU -lGLEW

all: $(obj)
	$(CPP) $(obj) $(lib) $(FLAGS) -o a
	
clean:
	rm a
	rm *.o


%.o : %.cpp Makefile
	$(CPP) $< -o $@ -c $(lib) $(FLAGS)
