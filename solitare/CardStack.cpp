#include "CardStack.h"


//////////////////////////  카드 스택

CardStack::CardStack()
{
	unsigned int stack_cnt, temp;
	Card * Header;

	remain = 0;
	srand((unsigned int)time(NULL));
	temp = rand() % NUMBER_OF_CARD;
	csCardStack = new Card(temp);
	//cout << "스택: 카드 생성 -> ";
	//cout << temp << endl;

	for (stack_cnt = 0; stack_cnt < NUMBER_OF_CARD - 1; stack_cnt++)
	{
		do
		{
			temp = rand() % NUMBER_OF_CARD;
			Header = csCardStack;
			while (Header != NULL)
			{
				if (Header->GetIndex() == temp)
				{
					temp = NUMBER_OF_CARD;
					break;
				}
				if (Header->nextCard == NULL)
				{
					Header->nextCard = new Card(temp);
					break;
				}
				Header = Header->nextCard;
			}
		} while (temp == NUMBER_OF_CARD);

		//cout << stack_cnt;
		//cout << " 스택: 카드 생성 -> ";
		//cout << temp << endl;
		remain++;
	}
}

CardStack::~CardStack()
{
	Card * Header;

	while (!IsEmpty())
	{
		Header = csCardStack;
		//cout << "스택: 카드 소멸 -> ";
		//cout << Header->GetIndex() << endl;
		csCardStack = csCardStack->nextCard;
		delete Header;
	}
}

bool CardStack::IsEmpty(void)
{
	return (csCardStack == NULL);
}

Card * CardStack::PopCard(void)
{
	Card * RetCard;

	RetCard = csCardStack;
	csCardStack = csCardStack->nextCard;
	RetCard->prevCard = NULL;
	RetCard->nextCard = NULL;
	remain--;

	return RetCard;
}