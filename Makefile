dodgeGame: meteor.o dodgeGame.o
	g++ dodgeGame.o meteor.o -o dodgeGame -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

meteor.o:
	g++ -c meteor.cpp

dodgeGame.o:
	g++ -c dodgeGame.cpp

clean:
	rm -rf dodgeGame dodgeGame.o meteor.o