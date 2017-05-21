#ifndef __CARD_H__
#define __CARD_H__

#include <iostream>
using namespace std;
#include <iomanip>
#include <ctime>
#include <string>


#define NUMBER_OF_CARD		(4*13)

typedef enum card_pattern {
	CARD_CLOVER,
	CARD_DIAMOND,
	CARD_HEART,
	CARD_SPADE
} CardPattern;

typedef enum card_number {
	CARD_ACE,
	CARD_TWO,
	CARD_THREE,
	CARD_FOUR,
	CARD_FIVE,
	CARD_SIX,
	CARD_SEVEN,
	CARD_EIGHT,
	CARD_NINE,
	CARD_TEN,
	CARD_JACK,
	CARD_QUEEN,
	CARD_KING
} CardNumber;

class Card
{
public:
	CardPattern enPattern;
	CardNumber enNumber;
	Card * nextCard;
	Card * prevCard;

	Card(CardPattern pattern, CardNumber number);
	Card(unsigned int index);
	~Card();
	unsigned int GetIndex(void);
	string GetPattern(void);
	void Console_Print(void);
};


#endif // __CARD_H__