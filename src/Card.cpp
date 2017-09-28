/*
 * Card.cpp
 *
 *  Created on: Nov 18, 2016
 *      Author: yashars
 */

#include <Card.h>
#include <string>
#include <stdio.h>


using namespace std;

Card::Card(Shape shape): _shape(shape) { }

Card::~Card() { }

FigureCard::FigureCard(Figure figure, Shape shape):Card(shape), _figure(figure) {

}

string FigureCard::toString(){
	string v;
	string s;

	if(_figure==Jack)
		v="J";
	if(_figure==Queen)
		v="Q";
	if(_figure==King)
		v="K";
	if(_figure==Ace)
		v="A";

	if(getShape()==Club)
		s="C";
	if(getShape()==Diamond)
		s="D";
	if(getShape()==Heart)
		s="H";
	if(getShape()==Spade)
		s="S";

	return v+s;
}

int FigureCard::getNumber()  {
	Figure number= getFigure();

	switch (number)
	      {
	         case Jack:
	        	 return -4;
	        	 break;
	         case Queen:
	         	 return -3;
	         	 break;
	         case King:
	        	 return -2;
	         	break;
	         case Ace:
	         	return -1;
	         	break;
	      }
	   return 0;
}

int FigureCard::equals(Card& other){

	int inserted = this->getNumber();
	int toInsert = other.getNumber();

	string s1=this->toString();
	string s2=other.toString();

	char insertedShape = s1.at(s1.size()-1);
	char toInsertShape = s2.at(s2.size()-1);
	if(this==&other)
		return 0;
	if(toInsert>0)
		return -1;
	if(toInsert>inserted)
		return 1;
	if(toInsert<inserted)
		return -1;
	if((toInsert==inserted)&&(insertedShape>toInsertShape))
		return -1;
	if((toInsert==inserted)&&(insertedShape<toInsertShape))
		return 1;
	return 0;
	}

int NumericCard::equals(Card& other){

	int inserted = this->getNumber();
	int toInsert = other.getNumber();

	string s1=this->toString();
	string s2=other.toString();

	char insertedShape = s1.at(s1.size()-1);
	char toInsertShape = s2.at(s2.size()-1);
	if(this==&other)
		return 0;
	if(toInsert<0)
		return 1;
	if(toInsert>inserted)
		return 1;
	if(toInsert<inserted)
		return -1;
	if((toInsert==inserted)&&(insertedShape>toInsertShape))
		return -1;
	if((toInsert==inserted)&&(insertedShape<toInsertShape))
		return 1;
	return 0;
	}

FigureCard:: ~FigureCard(){ }

NumericCard::NumericCard(int number,Shape shape):Card(shape), _number(number) { }

string NumericCard::toString(){
	string s= stringNumeric();
	if(getShape()==Club)
		return s+"C";
	if(getShape()==Diamond)
		return s+"D";
	if(getShape()==Heart)
		return s+"H";
	if(getShape()==Spade)
		return s+"S";
	return "";
}

string NumericCard::stringNumeric(){
	stringstream s ;
	s<<_number;
	return s.str();
}

NumericCard:: ~NumericCard(){ }


Shape Card::getShape() const {
	return _shape;
}


Figure FigureCard::getFigure()  {
	return _figure;
}


int NumericCard::getNumber()  {
	return _number;
}





