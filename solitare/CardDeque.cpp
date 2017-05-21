#include "CardDeque.h"


//////////////////////////  카드그룹을 관리

CardDeque::CardDeque()
{
	CardBack = NULL;
	CardFront = NULL;
	GroupSize = 0;
	//cout << "deck created" << endl;
}

CardDeque::~CardDeque()
{
	Card * temp;

	while (!IsEmpty())
	{
		temp = CardBack;
		//cout << "deck card deleted -> ";
		//cout << temp->GetIndex() << endl;
		CardBack = CardBack->nextCard;
		delete temp;
	}
}

bool CardDeque::IsEmpty(void)
{
	return (CardBack == NULL);
}

bool CardDeque::PushCard_Front(Card * card)
{
	if (card == NULL)
	{
		return false;
	}
	if (IsEmpty())
	{
		CardBack = card;
		while (card->nextCard != NULL)
		{
			GroupSize++;
			card = card->nextCard;
		}
		CardFront = card;
	}
	else
	{
		CardFront->nextCard = card;
		card->prevCard = CardFront;
		while (card->nextCard != NULL)
		{
			GroupSize++;
			card = card->nextCard;
		}
		CardFront = card;
	}

	GroupSize++;

	return true;
}

Card * CardDeque::PopCard_Front(void)
{
	Card * return_value;

	if (IsEmpty())
	{
		return NULL;
	}
	else
	{
		return_value = CardFront;
		CardFront = CardFront->prevCard;
		return_value->prevCard = NULL;
		if (CardFront == NULL)
		{
			CardBack = NULL;
		}
		else
		{
			CardFront->nextCard = NULL;
		}
		GroupSize--;
		return return_value;
	}
}

Card * CardDeque::PopCards_Front(unsigned char order)
{
	Card * return_value;

	return_value = CardFront;

	while ((return_value != NULL) && (order > 0))
	{
		return_value = return_value->prevCard;
		order--;
		GroupSize--;
	}

	if (return_value != NULL)
	{
		GroupSize--;
		CardFront = return_value->prevCard;
		if (CardFront != NULL)	CardFront->nextCard = NULL;
		else					CardBack = CardFront;
		return_value->prevCard = NULL;
	}

	return return_value;
}

bool CardDeque::PopCard_Front(Card * card)
{
	if (card == NULL)
	{
		return false;
	}
	
	if (card->prevCard != NULL)
	{
		card->prevCard->nextCard = NULL;
		CardFront = card->prevCard;
		card->prevCard = NULL;
	}
	else
	{
		CardFront = NULL;
		CardBack = NULL;
	}

	while (card != NULL)
	{
		GroupSize--;
		card = card->nextCard;
	}

	return true;
}

Card * CardDeque::SeeCard_Front(void)
{
	return CardFront;
}


bool CardDeque::PushCard_Back(Card * card)
{
	if (card == NULL)
	{
		return false;
	}
	if (IsEmpty())
	{
		CardFront = card;
		while (card->prevCard != NULL)
		{
			GroupSize++;
			card = card->prevCard;
		}
		CardBack = card;
	}
	else
	{
		CardBack->prevCard = card;
		card->nextCard = CardBack;
		while (card->prevCard != NULL)
		{
			GroupSize++;
			card = card->prevCard;
		}
		CardBack = card;
	}

	GroupSize++;

	return true;
}

Card * CardDeque::PopCard_Back(void)
{
	Card * return_value;

	if (IsEmpty())
	{
		return NULL;
	}
	else
	{
		return_value = CardBack;
		CardBack = CardBack->nextCard;
		return_value->nextCard = NULL;
		if (CardBack == NULL)
		{
			CardFront = NULL;
		}
		else
		{
			CardBack->prevCard = NULL;
		}
		GroupSize--;
		return return_value;
	}
}

Card * CardDeque::PopCards_Back(unsigned char order)
{
	Card * return_value;

	return_value = CardBack;

	while ((return_value != NULL) && (order > 0))
	{
		return_value = return_value->nextCard;
		order--;
		GroupSize--;
	}

	if (return_value != NULL)
	{
		GroupSize--;
		CardBack = return_value->nextCard;
		if (CardBack != NULL)	CardBack->prevCard = NULL;
		else					CardFront = CardBack;
		return_value->nextCard = NULL;
	}

	return return_value;
}

Card * CardDeque::SeeCard_Back(void)
{
	return CardBack;
}

Card * CardDeque::SeeCard(unsigned char position)
{
	int i;
	Card * temp = CardBack;

	if (temp == NULL)
		return NULL;

	for (i = 0; (i < position) && (temp != NULL); i++)
	{
		temp = temp->nextCard;
	}
	return temp;
}

void CardDeque::Console_Print(void)
{
	unsigned int i;
	Card * card;
	cout << "[0x" << hex << this << "] ";

	if (GroupSize > 0)
	{
		for (i = 0; i < GroupSize; i++)
		{
			card = CardDeque::SeeCard(i);
			cout << card->GetPattern() << card->enNumber + 1 << " ";
			if (i % 10 == 9)
				cout << endl;
		}
	}
	else
	{
		cout << dec << "NULL";
	}
	cout << dec << endl;
}

