#pragma once
#include "Card.h"

class CardStack
{
private:
	Card * csCardStack;
public:
	unsigned char remain;
	CardStack();
	~CardStack();
	bool IsEmpty(void);
	Card * PopCard(void);
};
