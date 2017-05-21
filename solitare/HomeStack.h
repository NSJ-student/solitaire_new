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
	bool PutCard(Card * card);				// Deck�� ī�带 �ִ´�
	Card * GetCard(unsigned int position=0);// Deck���� ī�带 �� �� ����
	bool BackCard(Card * card);
	void CardMoved(void) {}
	bool WithdrawCard(Card * card);
};

#endif // __HomeStack_H__