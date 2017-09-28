/*
 * Deck.cpp
 *
 *  Created on: Nov 22, 2016
 *      Author: yashars
 */

#include <Deck.h>
#include <stdlib.h>

	Deck::Deck():_deck(){ }

	Card* Deck:: fetchCard() {
		Card* s= _deck.top();
		_deck.pop();
		return s;
	}

	int Deck:: getNumberOfCards() {
		return _deck.size();
	}

	string Deck:: toString(){
		string s="";
		stack <Card*> temp;
		while (_deck.size()>0){
			s=s +_deck.top()->toString()+" ";
			temp.push(_deck.top());
			_deck.pop();
		}
		while (temp.size()>0){
			_deck.push(temp.top());
			temp.pop();
				}
		return s;
	}

	void Deck:: createDeck(string stringOfDeck){
		stack <Card*> s1;
			for (unsigned int i=0; i<stringOfDeck.size(); i++){
				string s;
				while(i<stringOfDeck.size()&& stringOfDeck.at(i)!=' '){
					s=s+stringOfDeck.at(i);
					i++;
				}
				char c= s.at(s.size()-1);
				Shape shape= createShape(c);
				if(s.at(0)=='A'||s.at(0)=='K'||s.at(0)=='Q'||s.at(0)=='J'){
					Figure figure = createFigure(s.at(0));
					FigureCard* card= new FigureCard(figure, shape);
					s1.push(card);
				}
				else{
					int number;
					string sub=s.substr(0,s.size()-2);
					number= atoi(s.c_str());
					NumericCard* card= new NumericCard(number, shape);
					s1.push(card);
				}
			}
			while(!(s1.empty())){
				_deck.push(s1.top());
				s1.pop();
			}
	}

	Shape Deck:: createShape(char shape){
		Shape s;

		switch (shape)
		      {
		         case 'C':
		        	 s= Club;
		        	 break;
		         case 'D':
		         	 s= Diamond;
		         	 break;
		         case 'H':
		        	 s= Heart;
		         	break;
		         case 'S':
		         	s= Spade;
		         	break;
		      }
		   return s;
	}
	Figure Deck:: createFigure(char figure){
		Figure f;

			switch (figure)
			      {
			         case 'J':
			        	 f= Jack;
			        	 break;
			         case 'Q':
			         	 f= Queen;
			         	 break;
			         case 'K':
			        	 f= King;
			         	break;
			         case 'A':
			         	f= Ace;
			         	break;
			      }
			   return f;
	}

	bool Deck:: isEmpty(){
		return this->_deck.empty();
	}

	Deck:: Deck (const Deck &other): _deck(){
		copy(other);
	}

	void Deck:: copy (const Deck &other){
		stack <Card*> otherCopy(other._deck);
		stack <Card*> temp;
		while(!(otherCopy.empty())){
			Card* copyCard;
			if (otherCopy.top()->getNumber()<0){
				Figure f;
				switch (otherCopy.top()->getNumber()) {
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
				copyCard= new FigureCard(f,otherCopy.top()->getShape() );
			}
			if (otherCopy.top()->getNumber()>0){
				copyCard= new NumericCard(otherCopy.top()->getNumber(),otherCopy.top()->getShape() );
			}
			temp.push(copyCard);
			otherCopy.pop();
		}
		while(!(temp.empty())){
			_deck.push(temp.top());
			temp.pop();
		}
	}

	Deck:: ~Deck(){
		clear();
	}

	void Deck:: clear(){
		while (!(_deck.empty())){
				delete _deck.top();
				_deck.pop();
			}
	}

	Deck& Deck::operator=(const Deck &other){
		if(this==&other)
			return *this;
		clear();
		copy(other);
		return *this;
	}





