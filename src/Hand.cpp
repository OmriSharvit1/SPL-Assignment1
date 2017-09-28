/*
 * Hand.cpp
 *
 *  Created on: Nov 19, 2016
 *      Author: yashars
 */

#include <Hand.h>



void Hand::discard4SimilarCards() {
	list <Card*> ::iterator it=_handCards.begin();
	list <Card*> ::iterator it2=_handCards.begin();
	it2++;


	int count=0;


	while (it2!=_handCards.end()){
		int s = (*it)->getNumber();
		int s2 =(*it2)->getNumber();
		if(s==s2){
			count++;
		}
		else {
			count=0;
		}
		if (count == 3) {
			Card* d1;
			d1 = *it2;

			it2--;
			Card* d2;
			d2 = *it2;

			it2--;
			Card* d3;
			d3 = *it2;

			it2--;
			Card* d4;
			d4 = *it2;

			removeCard(*d1);
			removeCard(*d2);
			removeCard(*d3);
			removeCard(*d4);
			delete (d1);
			delete (d2);
			delete (d3);
			delete (d4);
			count = 0;
			break;
		}
		else{
			it2++;
			it++;
		}
	}
}


Hand::Hand(): _handCards(){
}

bool Hand::addCard(Card &card) {
	Card* toInsert= &card;
	list <Card*> ::iterator it=_handCards.begin();
	if(_handCards.size()==0){
		_handCards.push_back (toInsert);
	}
	else{
		while(it!=_handCards.end()){
			if((**it).equals(card)<0){
				_handCards.insert(it, toInsert);
				discard4SimilarCards();
				return true;
			}
			it++;
		}
		_handCards.push_back(toInsert);
	}
	discard4SimilarCards();
return true;
}

bool Hand::removeCard(Card &card ) {
	if(search(card)){
		list <Card*> ::iterator it=_handCards.begin();
		while ((*it)->equals(card)!=0)
			it++;
		_handCards.remove(*it);
		return true;
	}
	return false;
}

bool Hand::search(Card &card){
	bool found=false;
	list <Card*> ::iterator it=_handCards.begin();
	while((it!=_handCards.end())&&(!found)){
		if((**it).equals(card)==0)
			found=true;
		it++;
	}
	return found;
}

int Hand::getNumberOfCards() {
	return _handCards.size();
}

string Hand::toString() {
	list <Card*> ::iterator it=_handCards.begin();
	string s="";
	for(unsigned int i=0; i<_handCards.size();i++){
		s=s+ (**it).toString()+" ";
		it++;
	}

	return s;
}


void Hand :: clear() {
	for(list<Card*>::iterator it=_handCards.begin(); it!= _handCards.end(); it++){
		delete (*it);
	}
}


 Hand::~Hand() {
	clear ();
}

list<Card*> Hand::getHand(){
	return _handCards;
}

bool Hand::isEmpty(){
	return _handCards.size()==0;
}


Hand:: Hand (const Hand &other):_handCards(){

	copy(other._handCards);
}

void Hand:: copy(list<Card*> otherCopy){

		Card* copyCard;
		list <Card*> ::iterator it=otherCopy.begin();

		while(it!=otherCopy.end()){

			if((*it)->getNumber()<0){
				Figure f;
				switch ((*it)->getNumber()) {
					case -4:
						f=Jack;
						break;
					case -3:
						f= Queen;
						break;
					case -2:
						f= King;
						break;
					case -1:
						f= Ace;
						break;
				}
				copyCard= new FigureCard(f,(*it)->getShape() );
			}
			if ((*it)->getNumber()>0){
			copyCard= new NumericCard((*it)->getNumber(),(*it)->getShape() );
			}
			_handCards.push_back(copyCard);
			it++;
		}
}

void Hand::setHand(list <Card*> h){
	copy(h);

}

Hand& Hand::operator=(const Hand &other){
	if(this==&other)
		return *this;
	clear();
	list<Card*> otherCopy(other._handCards);
	copy(otherCopy);
	return *this;
}




