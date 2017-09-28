#ifndef PLAYER_H_
#define PLAYER_H_

#include <iostream>

#include <Hand.h>
#include <Deck.h>
#include <vector>
#include <string>

using namespace std;

class Player : public Hand {
private:
	const string _name;

public:
	Player (string name);
	string getName() ;   //Returns the name of the player
	virtual int cardToAskFor()=0;
	Player* mostCardsAtHand(vector<Player*> p);
	Player* leastCardsAtHand(vector <Player*> p);
	virtual Player* fromWhoToAsk(vector <Player*> p)=0;
	int position(Player* p, vector <Player*> players);
	virtual int getPlayerType()=0;
	virtual ~Player();

};

class PlayerType1 : public Player {  //For strategy 1
private:
	int _playerType;
public:
	PlayerType1 (string name, int playerType);
	virtual int cardToAskFor();
	virtual Player* fromWhoToAsk(vector <Player*> p);
	virtual int getPlayerType();
	virtual ~PlayerType1();
};

class PlayerType2 : public Player {  //For strategy 2
private:
	int _playerType;

public:
	PlayerType2 (string name,int playerType );
	virtual int cardToAskFor();
	virtual Player* fromWhoToAsk(vector <Player*> p);
	virtual int getPlayerType();
	virtual ~PlayerType2();
};

class PlayerType3 : public Player {  //For strategy 3
private:
	unsigned int _nextToAsk;
	int _playerType;

public:
	PlayerType3 (string name, int playerType);
	virtual int cardToAskFor();
	virtual Player* fromWhoToAsk(vector <Player*> p);
	virtual int getPlayerType();
	virtual ~PlayerType3();
};

class PlayerType4 : public Player {  //For strategy 4
private:
	unsigned int _nextToAsk;
	int _playerType;
public:
	PlayerType4 (string name, int playerType);
	virtual int cardToAskFor();
	virtual Player* fromWhoToAsk(vector <Player*> p);
	virtual int getPlayerType();
	virtual ~PlayerType4();
};

#endif
