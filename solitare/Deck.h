#ifndef __Deck_H__
#define __Deck_H__
#include "Card.h"
#include "CardStack.h"
#include "CardDeque.h"

#define Deck_SIZE_MAX	24

class Deck : public CardDeque
{
private:
	Card * VisibleCard;
	unsigned char FlipNumber;
public:
	Deck();
	Deck(CardStack * stack);
	~Deck();
	bool PushStack(Card * card);	// ���ÿ� ī�带 �ִ´�(�ʱ�ȭ)
	Card * FlipCard(void);			// Deck���� ī�带 ���� �����´�
	Card * SeeVisibleCard(void);
	///////
	bool PutCard(Card * card) { return false; }	// ī�� ����
	Card * GetCard(unsigned int position=0);	// ī�� ��
	bool BackCard(Card * card);					// ������ ī�带 �ǵ���
	bool BackCard(void);						// Flip ���
	void CardMoved(void) {}
	bool WithdrawCard(Card * card);
};

#endif // __Deck_H__