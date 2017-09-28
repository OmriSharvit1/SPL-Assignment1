#ifndef CARD_H_
#define CARD_H_

#include <iostream>
#include <string>
#include <sstream>


using namespace std;

enum Shape {
	Club,
	Diamond,
	Heart,
	Spade
};

enum Figure {
	Jack,
	Queen,
	King,
	Ace
};

class Card {
private:
  Shape _shape;
public:
  virtual string toString() = 0; //Returns the string representation of the card "<value><shape>" exp: "12S" or "QD"

  virtual ~Card();
  Card(Shape shape);
  virtual Shape getShape() const;
  virtual int getNumber()=0;
  virtual int equals(Card &other)=0;

};

class FigureCard : public Card {
private:
	Figure _figure;

public:
	virtual string toString() override;
	FigureCard(Figure figure, Shape shape);
	virtual ~FigureCard();
	virtual Figure getFigure() ;
	virtual int getNumber() override;
	virtual int equals(Card &other);


};

class NumericCard : public Card {
private:
	int _number;
public:
	virtual string toString() override;
	NumericCard(int number, Shape shape);
	virtual ~NumericCard();
	string stringNumeric();
	virtual int getNumber() override;
	virtual int equals(Card &other);
};

#endif
