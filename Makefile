SOURCES=main.cpp Client.cpp InputParser.cpp RequestMaker.cpp buffer.cpp
CFLAGS=-Wall
build:
	g++ $(SOURCES) -o client $(CFLAGS)
run:
	./client

clean:
	rm client
