#include "Solitaire.h"

Solitaire::Solitaire(HINSTANCE hInstance, HWND hWnd, TIMERPROC tProc)
{
	unsigned int i;
	
	Stack = new CardStack();					// 52개의 카드를 만든다
	Pile = new Deck(Stack);						// Deck에 Stack의 카드를 할당
	for (i = 0; i < 4; i++)
	{
		Foundation[i] = new HomeStack();		// HomeStack 객체를 만든다
	}
	for (i = 0; i < 7; i++)
	{
		Tableau[i] = new Column(Stack, i + 1);	// Column에 Stack의 카드를 할당
	}
	Status = new StatusBar(hWnd);				// StatusBar를 관리할 객체
	Draw = new DrawCard(hInstance, hWnd);		// 클라이언트 화면에 표시할 버퍼 비트맵을 관리하는 객체

	MovingCard = NULL;
	MovedCard = NULL;
	MovedDeck_From = NULL;
	MovedDeck_To = NULL;
	PrevDeck = NULL;
	m_card_x = 0;
	m_card_y = 0;
	offset_x = 0;
	offset_y = 0;
	Score = 0;
	Time = 0;
	bRun = true;

	DrawAll(hWnd);
	SetTimer(hWnd, 1, 1000, tProc);
}
Solitaire::~Solitaire()
{
	if (MovingCard != NULL)
	{
		delete MovingCard;
	}
	delete Draw;
	delete Foundation[3];
	delete Pile;
	delete Stack;
	delete Tableau[6];
	delete Status;
}

void Solitaire::DrawAll(HWND hWnd)
{
	HDC hdc;
	RECT window_rect, taskbar_rect;
	unsigned int i;

	hdc = GetDC(hWnd);
	Draw->DrawBackground(hdc);
	Draw->DrawDeck(hdc, Pile);
	for (i = 0; i < 4; i++)
		Draw->DrawHomeStack(hdc, Foundation[i], i);
	for (i = 0; i < 7; i++)
		Draw->DrawColumn(hdc, Tableau[i], i);
	if (MovingCard != NULL)
	{
		Draw->DrawMovingCard(hdc, MovingCard, m_card_x - offset_x, m_card_y - offset_y);
	}
	ReleaseDC(hWnd, hdc);

	GetClientRect(hWnd, &window_rect);
	Status->GetArea(&taskbar_rect);
	window_rect.bottom -= (taskbar_rect.bottom);
	InvalidateRect(hWnd, &window_rect, FALSE);
}

HBITMAP Solitaire::GetDoubleBuffer(void)
{
	return Draw->GetDoubleBuffer();
}

CardLocation Solitaire::TranslateAxis(unsigned int x, unsigned int y)
{
	unsigned int i;
	if (IS_INSIDE_CARD(x, y, DECK_LEFT_X, DECK_LEFT_Y))
	{
		return DECK_STACK;
	}
	if (IS_INSIDE_CARD(x, y, DECK_RIGHT_X, DECK_RIGHT_Y))
	{
		return DECK_VISIBLE;
	}
	for (i = 0; i < 4; i++)
	{
		if (IS_INSIDE_CARD(x, y, HOMESTACK_X(i), HOMESTACK_Y))
		{
			return (CardLocation)(HOMESTACK1 + i);
		}
	}
	for (i = 0; i < 7; i++)
	{
		if (IS_INSIDE_CARDC(x, y, COLUMN_X(i), COLUMN_Y, CARD_WIDTH, Tableau[i]->TotalCardHeight()))
		{
			return (CardLocation)(COLUMN1 + i);
		}
	}
	return NOTHING;
}

bool Solitaire::CardDown(CardLocation location, unsigned int axis_x, unsigned int axis_y)
{
	if (IS_IN_THIS_AREA(location, DECK_STACK, DECK_STACK))
	{
		MovingCard = NULL;
		PrevDeck = Pile;
		return true;
	}
	else if (IS_IN_THIS_AREA(location, DECK_VISIBLE, DECK_VISIBLE))
	{
		MovingCard = Pile->GetCard();
		if (MovingCard != NULL)
		{
			m_card_x = axis_x;
			m_card_y = axis_y;
			offset_x = axis_x - DECK_RIGHT_X;
			offset_y = axis_y - DECK_RIGHT_Y;
			PrevDeck = Pile;
		}
		return true;
	}
	else if (IS_IN_THIS_AREA(location, HOMESTACK1, HOMESTACK4))
	{
		MovingCard = Foundation[location - HOMESTACK1]->GetCard();
		if (MovingCard != NULL)
		{
			m_card_x = axis_x;
			m_card_y = axis_y;
			offset_x = axis_x - HOMESTACK_X(location - HOMESTACK1);
			offset_y = axis_y - HOMESTACK_Y;
			PrevDeck = Foundation[location - HOMESTACK1];
			return true;
		}
	}
	else if (IS_IN_THIS_AREA(location, COLUMN1, COLUMN7))
	{
		unsigned int pos, off_y;
		pos = Tableau[location - COLUMN1]->TranslateToPosition(axis_y, &off_y);
		MovingCard = Tableau[location - COLUMN1]->GetCard(pos);
		if (MovingCard != NULL)
		{
			m_card_x = axis_x;
			m_card_y = axis_y;
			offset_x = axis_x - COLUMN_X(location - COLUMN1);
			offset_y = axis_y - off_y;
			PrevDeck = Tableau[location - COLUMN1];
			return true;
		}
	}
	else
	{
		MovingCard = NULL;
		PrevDeck = NULL;
		return false;
	}
}

bool Solitaire::CardUp(CardLocation location, unsigned int axis_y)
{
	if (PrevDeck == NULL)
	{
		return false;
	}

	if (IS_IN_THIS_AREA(location, DECK_STACK, DECK_STACK))
	{
		if ((MovingCard == NULL) && (PrevDeck == Pile))
		{
			Pile->FlipCard();
			MovedCard = MovingCard;
			MovedDeck_From = PrevDeck;
			MovedDeck_To = Pile;
		}
	}
	else if (IS_IN_THIS_AREA(location, HOMESTACK1, HOMESTACK4))
	{
		if (Foundation[location - HOMESTACK1]->PutCard(MovingCard) == false)
		{
			if (PrevDeck != NULL)	PrevDeck->BackCard(MovingCard);
		}
		else
		{
			GameScore(SCORE_TO_HOME_STACK);
			if (PrevDeck != NULL)	PrevDeck->CardMoved();
			MovedCard = MovingCard;
			MovedDeck_From = PrevDeck;
			MovedDeck_To = Foundation[location - HOMESTACK1];
		}
	}
	else if (IS_IN_THIS_AREA(location, COLUMN1, COLUMN7))
	{
		if (Tableau[location - COLUMN1]->PutCard(MovingCard) == false)
		{
			if (PrevDeck != NULL)	PrevDeck->BackCard(MovingCard);
		}
		else
		{
			if (PrevDeck == Pile)
			{
				GameScore(SCORE_DECK_TO_COLUMN);
			}
			if (PrevDeck != NULL)	PrevDeck->CardMoved();
			MovedCard = MovingCard;
			MovedDeck_From = PrevDeck;
			MovedDeck_To = Tableau[location - COLUMN1];
		}
	}
	else
	{
		if (PrevDeck != NULL) PrevDeck->BackCard(MovingCard);
	}

	MovingCard = NULL;
	PrevDeck = NULL;
	if (PrevDeck == NULL)	return false;
	else					return true;
}

bool Solitaire::CardDoubleClick(CardLocation location, unsigned int axis_y)
{
	unsigned int cnt;
	Card * card;

	if (IS_IN_THIS_AREA(location, DECK_VISIBLE, DECK_VISIBLE))
	{
		card = Pile->GetCard();
		for (cnt = 0; cnt < 4; cnt++)
		{
			if (Foundation[cnt]->PutCard(card))
			{
				Pile->CardMoved();
				MovedCard = card;
				MovedDeck_From = Pile;
				MovedDeck_To = Foundation[cnt];
				GameScore(SCORE_TO_HOME_STACK);
				return true;
			}
		}
		Pile->BackCard(card);
	}
	else if (IS_IN_THIS_AREA(location, COLUMN1, COLUMN7))
	{
		unsigned int pos;
		pos = Tableau[location - COLUMN1]->TranslateToPosition(axis_y, NULL);
		card = Tableau[location - COLUMN1]->GetCard(pos);
		for (cnt = 0; cnt < 4; cnt++)
		{
			if (Foundation[cnt]->PutCard(card))
			{
				Tableau[location - COLUMN1]->CardMoved();
				MovedCard = card;
				MovedDeck_From = Tableau[location - COLUMN1];
				MovedDeck_To = Foundation[cnt];
				GameScore(SCORE_TO_HOME_STACK);
				return true;
			}
		}
		Tableau[location - COLUMN1]->BackCard(card);
	}

	return false;
}

bool Solitaire::CardBack(void)
{
	if (MovedDeck_To != NULL)
	{
		if (MovedDeck_To == Pile)
		{
			Pile->BackCard();
			MovedCard = NULL;
			MovedDeck_From = NULL;
			MovedDeck_To = NULL;
			return true;
		}
		else if (MovedDeck_To->WithdrawCard(MovedCard))
		{
			MovedDeck_From->BackCard(MovedCard);
			for (int cnt = 0; cnt < 7; cnt++)
			{
				if (MovedDeck_To == Foundation[cnt])
				{
					GameScore(-SCORE_TO_HOME_STACK);
					break;
				}
				if (MovedDeck_To == Tableau[cnt])
				{
					GameScore(-SCORE_DECK_TO_COLUMN);
					break;
				}
			}
			MovedCard = NULL;
			MovedDeck_From = NULL;
			MovedDeck_To = NULL;
			return true;
		}
	}

	MovedCard = NULL;
	MovedDeck_From = NULL;
	MovedDeck_To = NULL;
	return false;
}

void Solitaire::UpdateCardAxis(unsigned int x, unsigned int y)
{
	m_card_x = x;
	m_card_y = y;
}

bool Solitaire::IsGameComplete(void)
{
	unsigned int cnt;
	Card * card;

	for (cnt = 0; cnt < 4; cnt++)
	{
		card = Foundation[cnt]->SeeCard();
		if (card == NULL)
		{
			return false;
		}
		if (card->enNumber != CARD_KING)
		{
			return false;
		}
	}

	return true;
}

void Solitaire::GameInfo(TCHAR * info)
{
	if (bRun)
	{
		Status->SetInfo(info);
	}
}

void Solitaire::GameScore(int scr)
{
	if (bRun)
	{
		Score += scr;
		Status->SetScore(Score);
	}
}

void Solitaire::GameTime(void)
{
	if (bRun)
	{
		Time++;
		Status->SetTime(Time);
	}
}

void Solitaire::GameStop(HWND hWnd)
{
	bRun = false;
	KillTimer(hWnd, 1);
}

bool Solitaire::IsGameRunning(void)
{
	return bRun;
}