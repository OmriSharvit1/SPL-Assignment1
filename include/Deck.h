#ifndef DECK_H_
#define DECK_H_

#include <iostream>

#include <Card.h>
#include <stack>

using namespace std;

class Deck {
private:
	stack <Card*> _deck;
	void copy (const Deck &other);
	void clear ();

public:
	Deck();
	Deck (const Deck &other);
	Deck& operator=(const Deck &other);
	Card* fetchCard();   //Returns the top card of the deck and remove it from the deck
	int getNumberOfCards(); // Get the number of cards in the deck
	string toString(); // Return the cards in top-to-bottom order in a single line, cards are separated by a space ex: "12S QD AS 3H"
	virtual ~Deck();
	void createDeck(string stringOfDeck);
	Shape createShape(char shape);
	Figure createFigure(char figure);
	bool isEmpty();



};

#endif
