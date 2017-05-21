#include "HomeStack.h"


HomeStack::HomeStack()
{
}

HomeStack::~HomeStack()
{
	////cout << "HomeStack Over" << endl;
}

bool HomeStack::PutCard(Card * card)
{
	Card * CurrentTopCard;

	if (card == NULL)
	{
		////cout << "�Է� ���� / no card" << endl;
		return false;
	}
	if (IsEmpty() && (card->enNumber != CARD_ACE))
	{
		//cout << "�Է� ���� " << card->enPattern << " / " << card->enNumber << " not ace" << endl;
		return false;
	}
	if (!IsEmpty())
	{
		CurrentTopCard = SeeCard_Front();
		if (CurrentTopCard->enNumber == CARD_KING)
		{
			//cout << "�Է� ���� " << card->enPattern << " / " << card->enNumber << " deck full" << endl;
			return false;
		}
		if (CurrentTopCard->enPattern != card->enPattern)
		{
			//cout << "�Է� ���� " << card->enPattern << " / " << card->enNumber << " pattern error" << endl;
			return false;
		}
		if (CurrentTopCard->enNumber + 1 != card->enNumber)
		{
			//cout << "�Է� ���� " << card->enPattern << " / " << card->enNumber << " number order error" << endl;
			return false;
		}
	}

	return CardDeque::PushCard_Front(card);
}

Card * HomeStack::GetCard(unsigned int position)
{
	return CardDeque::PopCard_Front();
}

Card * HomeStack::SeeCard(void)
{
	return CardDeque::SeeCard_Front();
}

bool HomeStack::BackCard(Card * card)
{
	return CardDeque::PushCard_Front(card);
}

bool HomeStack::WithdrawCard(Card * card)
{
	return CardDeque::PopCard_Front(card);
}
