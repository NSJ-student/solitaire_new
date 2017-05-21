#include "Card.h"



Card::Card(CardPattern pattern, CardNumber number)
{
	enPattern = pattern;
	enNumber = number;
	nextCard = NULL;
	prevCard = NULL;
}

Card::Card(unsigned int index)
{
	enPattern = (CardPattern)(index / 13);
	enNumber = (CardNumber)(index % 13);
	nextCard = NULL;
	prevCard = NULL;
}

Card::~Card()
{
}

unsigned int Card::GetIndex(void)
{
	return (enPattern * 13) + enNumber;
}

string Card::GetPattern(void)
{
	switch (enPattern)
	{
	case CARD_SPADE:	return "!";
	case CARD_CLOVER:	return "/";
	case CARD_DIAMOND:	return "#";
	case CARD_HEART:	return "@";
	default: return NULL;
	}
}

void Card::Console_Print(void)
{
	cout << GetPattern() << enNumber + 1 << " ";
}