#ifndef __HomeStack_H__
#define __HomeStack_H__

#include "Card.h"
#include "CardDeque.h"

class HomeStack : public CardDeque
{
private:
public:
	HomeStack();
	~HomeStack();
	Card * SeeCard(void);
	//////////
	bool PutCard(Card * card);				// Deck에 카드를 넣는다
	Card * GetCard(unsigned int position=0);// Deck에서 카드를 한 장 뺀다
	bool BackCard(Card * card);
	void CardMoved(void) {}
	bool WithdrawCard(Card * card);
};

#endif // __HomeStack_H__