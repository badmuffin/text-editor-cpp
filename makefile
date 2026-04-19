all:
	g++ main.cpp $(shell fltk-config --cxxflags --ldflags) -o app

run:
	./app

clean:
	rm -f app