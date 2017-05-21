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
	bool PushStack(Card * card);	// 스택에 카드를 넣는다(초기화)
	Card * FlipCard(void);			// Deck에서 카드를 한장 뒤집는다
	Card * SeeVisibleCard(void);
	///////
	bool PutCard(Card * card) { return false; }	// 카드 넣음
	Card * GetCard(unsigned int position=0);	// 카드 뺌
	bool BackCard(Card * card);					// 선택한 카드를 되돌림
	bool BackCard(void);						// Flip 취소
	void CardMoved(void) {}
	bool WithdrawCard(Card * card);
};

#endif // __Deck_H__