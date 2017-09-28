#ifndef HAND_H_
#define HAND_H_

#include <iostream>
#include <Card.h>
//#include <map>
#include <list>


using namespace std;

class Hand {
private:
		list<Card*> _handCards;
		void copy(list<Card*> otherCopy);
		void clear();


	// Declare here the collection of "Card *" of the hand
public:
	Hand ();
	Hand (const Hand &other);
	Hand & operator=(const Hand &other);


	bool search(Card &card);

	bool addCard(Card &card);
	bool removeCard(Card &card);
	int getNumberOfCards(); // Get the number of cards in hand
	string toString(); // Return a list of the cards, separated by space, in one line, in a sorted order, ex: "2S 5D 10H"
	virtual ~Hand();
	list<Card*> getHand();
	void discard4SimilarCards();
	bool isEmpty();
	void setHand(list<Card*> h);
};
#endif
