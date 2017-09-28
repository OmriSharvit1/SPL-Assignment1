/*
 * Player.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: yashars
 */
#include <Player.h>

Player::Player(string name):Hand(), _name(name) { }

Player::~Player() { }

string Player:: getName() {
	return _name;
}

PlayerType1::PlayerType1(string name, int playerType): Player(name), _playerType(playerType){ }

PlayerType1::~PlayerType1() { }

int PlayerType1::cardToAskFor(){
	list<Card*>_handCards= this->getHand();
	list <Card*> ::iterator it=_handCards.begin();
	list <Card*> ::iterator it2=_handCards.begin();
	list <Card*> ::iterator end=_handCards.end();

	end--;
	it2++;

	int count=0;
	int theMost=0;
	int toAsk=(*end)->getNumber();
	while (it!= _handCards.end()){
		if(it2!= _handCards.end() &&(*it)->getNumber()==(*it2)->getNumber()){
			count++;
		}
		else {
			if(theMost<=count){
				theMost=count;
				toAsk=(*it)->getNumber();
			}
			count=0;
		}
		it++;
		it2++;
	}
	return toAsk;
}

PlayerType2::PlayerType2(string name, int playerType): Player(name), _playerType(playerType){ }

PlayerType2::~PlayerType2() { }

int PlayerType2::cardToAskFor(){

	list<Card*> _handCards= this->getHand();
	list <Card*> ::iterator it=_handCards.begin();
	list <Card*> ::iterator it2=_handCards.begin();

	it2++;

	int count=0;
	int theLeast=4;
	int toAsk=(*it)->getNumber();

	while (it!= _handCards.end()){
		if(it2!= _handCards.end() && (*it)->getNumber()==(*it2)->getNumber()){
			while(it2!= _handCards.end()&& (*it)->getNumber()==(*it2)->getNumber()  ){
				count++;
				it++;
				it2++;
			}
			if(theLeast>count){
				theLeast=count;
				toAsk=(*it)->getNumber();
			}
		}
		else {
			if(theLeast>count){
				theLeast=count;
				toAsk=(*it)->getNumber();
			}
			count=0;
			it++;
			it2++;
		}
	}
	return toAsk;
}

PlayerType3 ::PlayerType3 (string name, int playerType): Player(name ), _nextToAsk(0), _playerType(playerType){ }

PlayerType3::~PlayerType3() { }

int PlayerType3::cardToAskFor(){
	list<Card*> _handCards= this->getHand();
	list <Card*> ::iterator it=_handCards.end();
	it--;
	return (*it)->getNumber();
}


PlayerType4 ::PlayerType4 (string name, int playerType): Player(name ), _nextToAsk(0), _playerType(playerType){ }

PlayerType4::~PlayerType4() { }

int PlayerType4::cardToAskFor(){
	list<Card*> _handCards= this->getHand();
	list <Card*> ::iterator it=_handCards.begin();
	return (*it)->getNumber();
}

Player* Player:: mostCardsAtHand(vector<Player*> p){
	int count=0;
	int theMost=0;
	Player* playerPlace=p[0];

	for(unsigned int i=0; i<p.size(); i++){
		count=p[i]->getNumberOfCards();
		if(theMost<=count && p[i]->getName()!=this->getName()){
			theMost=count;
			playerPlace=p[i];
		}
	}
	return playerPlace;
}


Player* Player:: leastCardsAtHand(vector <Player*> p){
	int count=0;
	int theLeast=p[0]->getNumberOfCards();
	Player* playerPlace=p[p.size()-1];
	for(unsigned int i=0; i<p.size(); i++){
		count=p[i]->getNumberOfCards();
		if(theLeast>=count){
			theLeast=count;
			playerPlace=p[i];
		}
	}
	return playerPlace;
}

Player* PlayerType1:: fromWhoToAsk(vector <Player*> p){
	return mostCardsAtHand(p);
}

Player* PlayerType2:: fromWhoToAsk(vector <Player*> p){
	return mostCardsAtHand(p);
}

Player* PlayerType3:: fromWhoToAsk(vector <Player*> p){
	Player* fromWhoToAsk;

	if (p[_nextToAsk]->getName()==this->getName()){
		if (_nextToAsk==p.size()-1){
			_nextToAsk=0;
			fromWhoToAsk=p[ _nextToAsk];
			_nextToAsk++;
		}
		else{
			_nextToAsk++;
			fromWhoToAsk=p[ _nextToAsk];
			if (_nextToAsk==p.size()-1)
				_nextToAsk=0;
			else
				_nextToAsk++;
		}
	}
	else{
		fromWhoToAsk=p[ _nextToAsk];
		if (_nextToAsk==p.size()-1)
			_nextToAsk=0;
		else
			_nextToAsk++;
	}
	return fromWhoToAsk;
}

Player* PlayerType4:: fromWhoToAsk(vector <Player*> p){
	Player* fromWhoToAsk;

	if (p[_nextToAsk]->getName()==this->getName()){
		if (_nextToAsk==p.size()-1){
			_nextToAsk=0;
			fromWhoToAsk=p[ _nextToAsk];
			_nextToAsk++;
		}
		else{
			_nextToAsk++;
			fromWhoToAsk=p[ _nextToAsk];
			if (_nextToAsk==p.size()-1)
				_nextToAsk=0;
			else
				_nextToAsk++;
		}
	}
	else{
		fromWhoToAsk=p[ _nextToAsk];
		if (_nextToAsk==p.size()-1)
			_nextToAsk=0;
		else
			_nextToAsk++;
	}
	return fromWhoToAsk;
}

int Player:: position(Player* p, vector <Player*> player){
	vector <Player*> ::iterator it=player.begin();
	int count=0;
	while (it!= player.end()){
		count++;
		if((*it)==p ){
			count++;
			return count;
		}
		else{
			count++;
			it++;
		}
	}
	return count;
}

int PlayerType1::getPlayerType(){
	return 1;
}

int PlayerType2::getPlayerType(){
	return 2;
}

int PlayerType3::getPlayerType(){
	return 3;
}

int PlayerType4::getPlayerType(){
	return 4;
}




