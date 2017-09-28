/*
 * Game.cpp
 *
 *  Created on: Nov 24, 2016
 *      Author: yashars
 */

#include <Game.h>
#include <Deck.h>
#include <stdlib.h>

Game::Game(char* configurationFile) :_players(),_deck() , _turn(0),_verbal(1), winner1(""), winner2("") {
	vector<string> lines;
	lines = readConfigurationFile(configurationFile);
	_verbal= atoi(lines[0].c_str());
	_deck.createDeck(lines[2]);
	unsigned int i = 3;
	while (i < lines.size()) {
		definePlayer(lines[i]);
		i++;
	}
}

void Game::definePlayer(string s) {
	char playerType = s.at(s.length() - 1);
	if (playerType == '1') {
		Player* p = new PlayerType1(s.substr(0, s.length() - 2), 1);
		_players.push_back(p);
	}
	if (playerType == '2') {
		Player* p = new PlayerType2(s.substr(0, s.length() - 2), 2);
		_players.push_back(p);
	}
	if (playerType == '3') {
		Player* p = new PlayerType3(s.substr(0, s.length() - 2), 3);
		_players.push_back(p);
	}
	if (playerType == '4') {
		Player* p = new PlayerType4(s.substr(0, s.length() - 2), 4);
		_players.push_back(p);
	}
}

vector<string> Game::readConfigurationFile(char* configurationFile) {
	ifstream file;
	file.open(configurationFile);
	vector<string> lines;
	string CurrentLine;
	while (getline(file, CurrentLine)) {
		if (!CurrentLine.empty() && CurrentLine[0] != '#' && CurrentLine[0] != ' '  ) {
			lines.push_back(CurrentLine);
		}
	}
	return lines;
}

void Game::init() {
	for (unsigned int i = 0; i < _players.size(); i++) {
		for (int j = 0; j < 7 && !(_deck.isEmpty()); j++)
			(_players[i])->addCard(*(_deck.fetchCard()));
	}
}

void Game::play() {
	bool notGameOver = true;
	while (notGameOver) {
		for (unsigned int i = 0; i < _players.size(); i++) {
			_turn++;
			if(_verbal==1){
				cout<<endl;
				cout<< "Turn "<<_turn<<endl;
				Game::printState();
			}
			string cardToAsk;
			int c = _players[i]->cardToAskFor();
			Player* p1 = _players[i];
			Player* p2 = p1->fromWhoToAsk(_players);
			if (c == -1)
				cardToAsk = "A";                 		// fix it
			else if (c == -2)
				cardToAsk = "K";
			else if (c == -3)
				cardToAsk = "Q";
			else if (c == -4)
				cardToAsk = "J";
			else
				cardToAsk = intToString(c);
			if(_verbal==1)
				cout << p1->getName() << " asked " << p2->getName()<< " for the value " << cardToAsk << endl;
			bool get = giveCard(p1->cardToAskFor(), p1, p2);
			if (!get && !(_deck.isEmpty())) {
				p1->addCard(*(_deck.fetchCard()));
			}
			if (p1->isEmpty() && p2->isEmpty()) {
				unsigned int j = p2->position(p2, _players);
				if (i < j) {
					winner1 = _players[i]->getName();
					winner2 = p2->getName();
					notGameOver = false;
					break;
				}
				else {
					winner1 = p2->getName();
					winner2 = _players[i]->getName();
					notGameOver = false;
					break;
				}
			}
			else if (p1->isEmpty()) {
				winner1 = _players[i]->getName();
				notGameOver = false;

				break;
			}
			else if (p2->isEmpty()) {
				winner1 = _players[i]->fromWhoToAsk(_players)->getName();
				notGameOver = false;
				break;
			}
		}
	}
}

string Game::intToString(int c) {
	stringstream s;
	s << c;
	return s.str();
}

bool Game::giveCard(int card, Player* toGive, Player* Gives) {
	bool getCard = false;
	list<Card*> playerGetHand = toGive->getHand();
	list<Card*> playerGiveHand = Gives->getHand();
	list<Card*>::iterator it = playerGiveHand.begin();
	int count = 0;
	while (it != playerGiveHand.end()) {
		int cardToCheck = (*it)->getNumber();
		if (cardToCheck == card) {
			count++;
			Card* give = *it;
			Gives->removeCard(*give);
			toGive->addCard(*give);

			getCard = true;
		}
		it++;
	}
	int i = 0;
	while (!(_deck.isEmpty()) && i < count) {
		Gives->addCard(*(_deck.fetchCard()));
		i++;
	}
	return getCard;
}

void Game::printState() {
	cout << "Deck: " << _deck.toString() << endl;
	for (unsigned int i = 0; i < _players.size(); i++)
		cout << _players[i]->getName() << ": " << _players[i]->toString()
				<< endl;
}

Game::~Game() {
	clear();
}

void Game::clear() {
	for (vector<Player*>::iterator it = _players.begin(); it != _players.end();
			++it) {
		delete *it;
	}
}

void Game::printNumberOfTurns() {
	cout << "Number of turns: " << _turn << endl;
}

void Game::printWinner() {
	if (winner2 == "") {
		cout << "***** The Winner is: " << winner1 << " *****" << endl;


	} else {
		cout << "***** The winners are: " << winner1 << " and " << winner2<< " *****" << endl;
	}
}

Game::Game(const Game &other) :_players(),_deck(other._deck), _turn(other._turn),_verbal(other._verbal), winner1(other.winner1), winner2(other.winner2) {
	copy(other);
}

void Game::copy(const Game &other) {

	vector<Player*> otherCopy(other._players);
	Player* copyPlayer;
	vector<Player*>::iterator it = otherCopy.begin();
	while (it != otherCopy.end()) {
		int type = (*it)->getPlayerType();
		if (type == 1)
			copyPlayer = new PlayerType1((*it)->getName(), 1);
		if (type == 2)
			copyPlayer = new PlayerType2((*it)->getName(), 2);
		if (type == 3)
			copyPlayer = new PlayerType3((*it)->getName(), 3);
		if (type == 4)
			copyPlayer = new PlayerType4((*it)->getName(), 4);

		copyPlayer->setHand((**it).getHand());
		_players.push_back(copyPlayer);
		list<Card*> otherCopy(copyPlayer->getHand());
		list<Card*>::iterator it2 = otherCopy.begin();
		it++;
	}
}

Game& Game::operator=(const Game &other){
	if(this==&other)
		return *this;
	clear();
	copy(other);
	return *this;
}


