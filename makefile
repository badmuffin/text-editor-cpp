all:
	fltk-config --compile main.cpp

run:
	./main

clean:
	rm -f main