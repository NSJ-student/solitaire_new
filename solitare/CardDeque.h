#ifndef __CARDDEQUE_H__
#define __CARDDEQUE_H__
#include "Card.h"


class CardDeque
{
private:
	Card * CardBack;		// �ٴ��� ī��	-> �ٴ� �� ī��
	Card * CardFront;		// �� �� ī��	-> ������ ī��� ���� ��

protected:
	unsigned int GroupSize;

	CardDeque();
	~CardDeque();
	bool IsEmpty(void);

	bool PushCard_Front(Card * card);
	Card * PopCard_Front(void);
	Card * PopCards_Front(unsigned char order);	// 0�� ù��°, Front���� ��
	bool PopCard_Front(Card * card);
	Card * SeeCard_Front(void);

	bool PushCard_Back(Card * card);
	Card * PopCard_Back(void);
	Card * PopCards_Back(unsigned char order);	// 0�� ù��°, Back���� ��
	Card * SeeCard_Back(void);

	Card * SeeCard(unsigned char position);

	virtual void Console_Print(void);
public:
	virtual bool PutCard(Card * card) = 0;				// ī�� ����
	virtual Card * GetCard(unsigned int position) = 0;	// ī�带 ��
	virtual void CardMoved(void) = 0;					// ī�尡 Ȯ���� �Ű���

	virtual bool BackCard(Card * card) = 0;				// ������ ī�带 �ǵ���
	virtual bool WithdrawCard(Card * card) = 0;			// �Ű��� ī�� ���
};


#endif //__CARDDEQUE_H__