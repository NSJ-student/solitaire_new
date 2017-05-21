#pragma once
#include "Card.h"
#include "CardStack.h"
#include "CardDeque.h"

class Column : public CardDeque
{
private:
	unsigned int HiddenSize;
	bool bExposed;
public:
	Column();
	Column(CardStack * stack, unsigned char size);
	~Column();
	bool PushStack(Card * card);				// 초기화를 위해 카드 넣음
	Card * SeeFirstCard(void);
	unsigned int GetHiddenSize();
	unsigned int GetGroupSize();
	unsigned int TranslateToPosition(unsigned int axis_y, unsigned int * offset_y);
	unsigned int TotalCardHeight(void);
	///////////
	bool PutCard(Card * card);				// 카드 넣음
	Card * GetCard(unsigned int position);	// 카드를 뺌
	void CardMoved(void);
	bool BackCard(Card * card);
	bool WithdrawCard(Card * card);
};
