#ifndef __CARDDEQUE_H__
#define __CARDDEQUE_H__
#include "Card.h"


class CardDeque
{
private:
	Card * CardBack;		// 바닥의 카드	-> 바닥 쪽 카드
	Card * CardFront;		// 맨 윗 카드	-> 유저가 카드는 빼는 쪽

protected:
	unsigned int GroupSize;

	CardDeque();
	~CardDeque();
	bool IsEmpty(void);

	bool PushCard_Front(Card * card);
	Card * PopCard_Front(void);
	Card * PopCards_Front(unsigned char order);	// 0이 첫번째, Front으로 뺌
	bool PopCard_Front(Card * card);
	Card * SeeCard_Front(void);

	bool PushCard_Back(Card * card);
	Card * PopCard_Back(void);
	Card * PopCards_Back(unsigned char order);	// 0이 첫번째, Back으로 뺌
	Card * SeeCard_Back(void);

	Card * SeeCard(unsigned char position);

	virtual void Console_Print(void);
public:
	virtual bool PutCard(Card * card) = 0;				// 카드 넣음
	virtual Card * GetCard(unsigned int position) = 0;	// 카드를 뺌
	virtual void CardMoved(void) = 0;					// 카드가 확실히 옮겨짐

	virtual bool BackCard(Card * card) = 0;				// 선택한 카드를 되돌림
	virtual bool WithdrawCard(Card * card) = 0;			// 옮겨진 카드 취소
};


#endif //__CARDDEQUE_H__