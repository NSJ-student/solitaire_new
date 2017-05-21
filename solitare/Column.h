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
	bool PushStack(Card * card);				// �ʱ�ȭ�� ���� ī�� ����
	Card * SeeFirstCard(void);
	unsigned int GetHiddenSize();
	unsigned int GetGroupSize();
	unsigned int TranslateToPosition(unsigned int axis_y, unsigned int * offset_y);
	unsigned int TotalCardHeight(void);
	///////////
	bool PutCard(Card * card);				// ī�� ����
	Card * GetCard(unsigned int position);	// ī�带 ��
	void CardMoved(void);
	bool BackCard(Card * card);
	bool WithdrawCard(Card * card);
};
