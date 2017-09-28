#ifndef GAME_H_
#define GAME_H_

#include <iostream>
#include <vector>
#include <Player.h>
#include <Deck.h>
#include<fstream>


using namespace std;

class Game {
private:
	vector<Player *> _players;  //The list of the players
	Deck _deck;                 //The deck of the game
	int _turn;
	int _verbal;
	string winner1;
	string winner2;
	void copy(const Game &other);
    void clear();


public:
	Game(char* configurationFile);
    Game(const Game &other);
	vector<string> readConfigurationFile(char* configurationFile);
	void init();
	void play();
	void printState();        //Print the state of the game as described in the assignment.
	void printWinner();       //Print the winner of the game as describe in the assignment.
    void printNumberOfTurns(); //Print the number of played turns at any given time.
    void definePlayer(string s);
    string intToString(int c);
    bool giveCard(int card,Player* toGive, Player* Gives);
    virtual ~Game();
	Game& operator=(const Game &other);
};

#endif
