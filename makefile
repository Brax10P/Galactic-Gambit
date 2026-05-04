#Macros

CC = g++
FLAGS = -Wall -std=c++17 
LINKS = -lsfml-graphics -lsfml-window -lsfml-system 
game: obj/main.o obj/game.o obj/welcome.o obj/play.o obj/button.o obj/results.o obj/howto.o
	$(CC) $(FLAGS) $^ -o $@ $(LINKS)

obj/main.o: src/main.cpp header/game.h
	$(CC) $(FLAGS) -c $< -o obj/main.o

obj/howto.o: src/howto.cpp header/howto.h
	$(CC) $(FLAGS) -c $< -o obj/howto.o
	
obj/game.o: src/game.cpp header/game.h header/states.h header/welcome.h header/play.h header/results.h
	$(CC) $(FLAGS) -c $< -o obj/game.o

obj/welcome.o: src/welcome.cpp header/welcome.h header/states.h header/button.h
	$(CC) $(FLAGS) -c $< -o obj/welcome.o

obj/play.o: src/play.cpp header/play.h header/states.h header/button.h 
	$(CC) $(FLAGS) -c $< -o obj/play.o

obj/button.o: src/button.cpp header/button.h
	$(CC) $(FLAGS) -c $< -o obj/button.o

obj/results.o: src/results.cpp header/results.h header/states.h header/button.h
	$(CC) $(FLAGS) -c $< -o obj/results.o

clean:
	rm -f game *.o

test: TESTS/test.cpp TESTS/catch_amalgamated.cpp src/play.cpp src/button.cpp header/play.h header/button.h header/states.h
	$(CC) $(FLAGS) TESTS/test.cpp TESTS/catch_amalgamated.cpp src/play.cpp src/button.cpp -o test $(LINKS)
	./test