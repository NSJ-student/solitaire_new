#include "Deck.h"


Deck::Deck()
{
	VisibleCard = NULL;
	FlipNumber = 0;
}

Deck::Deck(CardStack * stack)
{
	int i;
	Card * temp;

	FlipNumber = 0;
	VisibleCard = NULL;
	for (i = 0; i < Deck_SIZE_MAX; i++)
	{
		temp = stack->PopCard();
		if (temp == NULL)
		{
			//cout << "Deck initialize Error: Card Lack\n";
		}
		CardDeque::PushCard_Front(temp);
	}
}

Deck::~Deck()
{
	//cout << "Deck Over" << endl;
}

bool Deck::PushStack(Card * card)
{
	return CardDeque::PushCard_Front(card);
}

Card * Deck::FlipCard(void)
{
	if (FlipNumber < GroupSize)
	{
		VisibleCard = CardDeque::PopCard_Back();
		CardDeque::PushCard_Front(VisibleCard);
		FlipNumber++;
	}
	else
	{
		VisibleCard = NULL;
		FlipNumber = 0;
	}

	return VisibleCard;
}

Card * Deck::GetCard(unsigned int position)
{
	Card * temp;

	if (VisibleCard == NULL)
	{
		return NULL;
	}
	else
	{
		temp = CardDeque::PopCard_Front();
		if (temp != NULL)
		{
			FlipNumber--;
			VisibleCard = CardDeque::SeeCard_Front();
			if (FlipNumber == 0)
			{
				VisibleCard = NULL;
			}
		}

		return temp;
	}
}

Card * Deck::SeeVisibleCard(void)
{
	return VisibleCard;
}

bool Deck::BackCard(Card * card)
{
	if (card == NULL)
	{
		return false;
	}

	FlipNumber++;
	VisibleCard = card;
	return CardDeque::PushCard_Front(card);
}

bool Deck::BackCard(void)
{
	if (GroupSize == 0)
	{
		return false;
	}
	if (VisibleCard == NULL)
	{
		FlipNumber = GroupSize;
	}
	else
	{
		VisibleCard = CardDeque::PopCard_Front();
		CardDeque::PushCard_Back(VisibleCard);
		FlipNumber--;
	}

	if (FlipNumber == 0)
	{
		VisibleCard = NULL;
	}
	else
	{
		VisibleCard = CardDeque::SeeCard_Front();
	}

	return true;
}

bool Deck::WithdrawCard(Card * card)
{
	FlipNumber++;
	return CardDeque::PopCard_Front(card);
}