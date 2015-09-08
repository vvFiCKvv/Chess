all :
	gcc lib/*.cpp *.cpp -lglut -o chess
debug:
	gcc lib/*.cpp *.cpp -lglut -o chess -Wall -DDEBUG -g
clean:
	rm chess
