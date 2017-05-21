#include "Column.h"
#include "DrawCard.h"


Column::Column(void)
{
	HiddenSize = 0;
	bExposed = false;
}

Column::Column(CardStack * stack, unsigned char size)
{
	int i;
	Card * temp;

	for (i = 0; i < size; i++)
	{
		temp = stack->PopCard();
		if (temp == NULL)
		{
			//cout << "Column initialize Error: Card Lack\n";
		}
		CardDeque::PushCard_Front(temp);
	}
	HiddenSize = size - 1;
	bExposed = false;
}

Column::~Column(void)
{
	//cout << "Column Over" << endl;
}

bool Column::PushStack(Card * card)
{
	bool rvalue;
	rvalue = CardDeque::PushCard_Front(card);
	HiddenSize = GroupSize - 1;

	return rvalue;
}

bool Column::PutCard(Card * card)
{
	Card * Tail = CardDeque::SeeCard_Front();

	if (card == NULL)
		return false;

	if (Tail == NULL)
	{
		//cout << "Column: push succeed\n";
		return CardDeque::PushCard_Front(card);
	}
	if (Tail->enPattern != card->enPattern)
	{
		if ((Tail->enPattern + card->enPattern) != 3)		// 색이 다름
		{
			if (Tail->enNumber - 1 == card->enNumber)		// 카드 숫서가 맞음
			{
				//cout << "Column: push succeed\n";
				return CardDeque::PushCard_Front(card);
			}
		}
	}
	//cout << "Column: push fail\n";

	return false;
}

Card * Column::GetCard(unsigned int position)
{
	Card * ret;
	if (position + 1 <= HiddenSize)	// 선택 카드가 가려진 카드
	{
		//cout << "Column: Hidden\n";
		return NULL;
	}
	if (position + 1 > GroupSize)				// 선택 카드 없음
	{
		//cout << "Column: no select\n";
		return NULL;
	}

	ret = CardDeque::PopCards_Front(GroupSize - 1 - position);
	//if ((GroupSize == HiddenSize) && (CardDeque::SeeCard_Front() != NULL))
	//{
	//	HiddenSize--;
	//	ExposedFlag = 1;
	//}
	//else
	//{
	//	ExposedFlag = 0;
	//}

	return ret;
}

void Column::CardMoved(void)
{
	bExposed = false;
	if (GroupSize != 0)
	{
		if (GroupSize == HiddenSize)
		{
			bExposed = true;
			HiddenSize--;
		}
	}
}

Card * Column::SeeFirstCard(void)
{
	return CardDeque::SeeCard_Back();
}

unsigned int Column::GetHiddenSize()
{
	return HiddenSize;
}

unsigned int Column::GetGroupSize()
{
	return GroupSize;
}

bool Column::BackCard(Card * card)
{
	bool bRet = CardDeque::PushCard_Front(card);
	if (bExposed && bRet)
	{
		if (GroupSize > HiddenSize+1)
		{
			HiddenSize++;
		}
		bExposed = false;
	}
	return bRet;
}

bool Column::WithdrawCard(Card * card)
{
	return CardDeque::PopCard_Front(card);
}

unsigned int Column::TranslateToPosition(unsigned int axis_y, unsigned int * offset_y)
{
	unsigned int compare_y = COLUMN_Y;
	unsigned int position = 0;

	while (compare_y < axis_y)
	{
		if(offset_y != NULL) *offset_y = compare_y;
		if (position == GroupSize - 1)
		{
			if (axis_y < compare_y + CARD_HEIGHT)
			{
				return position;
			}
			else
			{
				return 0xFF;
			}
		}
		if (position < HiddenSize)
		{
			compare_y += HIDDEN_CARD_GAP;
		}
		else
		{
			compare_y += EXPOSED_CARD_GAP;
		}
		position++;
	}

	return position-1;
}

unsigned int Column::TotalCardHeight(void)
{
	unsigned int position = 0;
	unsigned int height = 0;

	if (GroupSize == 0)
	{
		return CARD_HEIGHT;
	}
	while (position < GroupSize)
	{
		if (position < HiddenSize)
		{
			if (position == GroupSize - 1)
			{
				height += CARD_HEIGHT;
			}
			else
			{
				height += HIDDEN_CARD_GAP;
			}
		}
		else if (position == GroupSize - 1)
		{
			height += CARD_HEIGHT;
		}
		else
		{
			height += EXPOSED_CARD_GAP;
		}
		position++;
	}

	return height;
}
