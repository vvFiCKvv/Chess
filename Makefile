all :
	gcc lib/*.cpp *.cpp -lglut -lGL -lstdc++ -fpermissive -o chess
debug:
	gcc lib/*.cpp *.cpp -lglut -lGL -lstdc++ -o chess -fpermissive -Wall -DDEBUG -g
clean:
	rm chess
