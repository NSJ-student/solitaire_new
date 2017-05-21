#include "DrawCard.h"
#include "resource.h"


DrawCard::~DrawCard()
{
	DeleteObject(hCardBitmap);
	DeleteObject(hDBuff);
	DeleteObject(CardBrush);
	DeleteObject(BackgroundBrush);
}

DrawCard::DrawCard(HINSTANCE instance, HWND wnd)
{
	RECT WndRect;
	HDC hDC;

	hInstance = instance;
	hWnd = wnd;
	GetClientRect(hWnd, &WndRect);
	hDC = GetDC(hWnd);

	hDBuff = CreateCompatibleBitmap(hDC, WndRect.right, WndRect.bottom);
	hCardBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CARD));

	CardBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
	BackgroundBrush = CreateSolidBrush(RGB(0, 255, 0));

	ReleaseDC(hWnd, hDC);
}

void DrawCard::Init(HINSTANCE instance, HWND wnd)
{
	RECT WndRect;
	HDC hDC;

	hInstance = instance;
	hWnd = wnd;
	GetClientRect(hWnd, &WndRect);
	hDC = GetDC(hWnd);

	hDBuff = CreateCompatibleBitmap(hDC, WndRect.right, WndRect.bottom);
	hCardBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CARD));

	CardBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
	BackgroundBrush = CreateSolidBrush(RGB(0, 255, 0));

	ReleaseDC(hWnd, hDC);
}

void DrawCard::DrawMovingCard(HDC hDC, Card * card, unsigned int x, unsigned int y)
{
	HDC hBufDC, hCardDC;
	HBITMAP OldBitmap, OldBitmap2;// , CardBitmap;

	hBufDC = CreateCompatibleDC(hDC);
	OldBitmap = (HBITMAP)SelectObject(hBufDC, hDBuff);
	hCardDC = CreateCompatibleDC(hDC);
	//CardBitmap = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_CARD));
	OldBitmap2 = (HBITMAP)SelectObject(hCardDC, hCardBitmap);

	while (card != NULL)
	{
		// 그리기
		BitBlt(hBufDC, x, y, CARD_WIDTH, CARD_HEIGHT,
			hCardDC, card->enPattern*CARD_WIDTH, card->enNumber*CARD_HEIGHT, SRCCOPY);
		y += EXPOSED_CARD_GAP;
		card = card->nextCard;
	}
	// 정리
	SelectObject(hBufDC, OldBitmap);
	DeleteDC(hBufDC);	
	SelectObject(hCardDC, OldBitmap2);
	//DeleteObject(CardBitmap);
	DeleteObject(hCardDC);
}

void DrawCard::DrawDeck(HDC hDC, Deck * Deck)
{
	HDC hBufDC, hCardDC;
	HBITMAP OldBitmap, OldBitmap2;// , CardBitmap;
	HBRUSH OldBrush;
	Card * card = Deck->SeeVisibleCard();

	// 준비
	hBufDC = CreateCompatibleDC(hDC);
	OldBitmap = (HBITMAP)SelectObject(hBufDC, hDBuff);
	hCardDC = CreateCompatibleDC(hDC);
	OldBitmap2 = (HBITMAP)SelectObject(hCardDC, hCardBitmap);
	OldBrush = (HBRUSH)SelectObject(hBufDC, CardBrush);
	// 카드 덱 그리기
	Rectangle(hBufDC, DECK_LEFT_X, DECK_LEFT_Y, DECK_LEFT_X + CARD_WIDTH, DECK_LEFT_Y + CARD_HEIGHT);

	if (card != NULL)
	{
		// 그리기
		BitBlt(hBufDC, DECK_RIGHT_X, DECK_RIGHT_Y, CARD_WIDTH, CARD_HEIGHT,
			hCardDC, card->enPattern*CARD_WIDTH, card->enNumber*CARD_HEIGHT, SRCCOPY);
	}
	else
	{
		// 그리기
		//DeleteObject(MyBrush);
		//MyBrush = CreateSolidBrush(RGB(0, 0, 0));
		//(HBRUSH)SelectObject(hBufDC, MyBrush);
		//Rectangle(hBufDC, DECK_RIGHT_X, DECK_RIGHT_Y, DECK_RIGHT_X + CARD_WIDTH, DECK_RIGHT_Y+CARD_HEIGHT);
	}
	// 정리
	SelectObject(hBufDC, OldBitmap);
	SelectObject(hCardDC, OldBitmap2);
	SelectObject(hBufDC, OldBrush);
	DeleteDC(hBufDC);
	DeleteObject(hCardDC);
}


void DrawCard::DrawHomeStack(HDC hDC, HomeStack * HomeStack, unsigned int position)
{
	HDC hBufDC, hCardDC;
	HBITMAP OldBitmap, OldBitmap2;// , CardBitmap;
	Card * card = HomeStack->SeeCard();

	hBufDC = CreateCompatibleDC(hDC);
	OldBitmap = (HBITMAP)SelectObject(hBufDC, hDBuff);
	hCardDC = CreateCompatibleDC(hDC);
	OldBitmap2 = (HBITMAP)SelectObject(hCardDC, hCardBitmap);

	if (card != NULL)
	{
		// 그리기
		BitBlt(hBufDC, HOMESTACK_X(position), HOMESTACK_Y, CARD_WIDTH, CARD_HEIGHT,
			hCardDC, card->enPattern*CARD_WIDTH, card->enNumber*CARD_HEIGHT, SRCCOPY);
	}
	else
	{
		// 그리기
		//MyPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
		//OldPen = (HPEN)SelectObject(hBufDC, MyPen);
		//MyBrush = CreateHatchBrush(HS_DIAGCROSS, RGB(255, 0, 0));
		//OldBrush = (HBRUSH)SelectObject(hBufDC, MyBrush);
		//Rectangle(hBufDC, HOMESTACK_X(position), HOMESTACK_Y, HOMESTACK_X(position) + CARD_WIDTH, HOMESTACK_Y + CARD_HEIGHT);
		//SelectObject(hBufDC, OldPen);
		//SelectObject(hBufDC, OldBrush);
		//DeleteObject(MyPen);
		//DeleteObject(MyBrush);
	}
	// 정리
	SelectObject(hBufDC, OldBitmap);
	DeleteDC(hBufDC);
	SelectObject(hCardDC, OldBitmap2);
	DeleteObject(hCardDC);
}


void DrawCard::DrawColumn(HDC hDC, Column * Column, unsigned int position)
{
	HDC hBufDC, hCardDC;
	HBITMAP OldBitmap, OldBitmap2;// , CardBitmap;
	HBRUSH OldBrush;
	unsigned int hidden = Column->GetHiddenSize();
	unsigned int gap = 0;
	Card * card = Column->SeeFirstCard();

	hBufDC = CreateCompatibleDC(hDC);
	OldBitmap = (HBITMAP)SelectObject(hBufDC, hDBuff);
	hCardDC = CreateCompatibleDC(hDC);
	OldBitmap2 = (HBITMAP)SelectObject(hCardDC, hCardBitmap);
	OldBrush = (HBRUSH)SelectObject(hBufDC, CardBrush);

	while (card != NULL)
	{
		// 그리기
		if (hidden > 0)
		{
			hidden--;
			Rectangle(hBufDC, COLUMN_X(position), COLUMN_Y + gap, 
							COLUMN_X(position) + CARD_WIDTH, COLUMN_Y + gap + CARD_HEIGHT);
			gap = gap + HIDDEN_CARD_GAP;
		}
		else
		{
			BitBlt(hBufDC, COLUMN_X(position), COLUMN_Y + gap, CARD_WIDTH, CARD_HEIGHT,
				hCardDC, card->enPattern*CARD_WIDTH, card->enNumber*CARD_HEIGHT, SRCCOPY);
			gap = gap + EXPOSED_CARD_GAP;
		}
		card = card->nextCard;
	}
	// 그리기
	SelectObject(hBufDC, OldBrush);
	// 정리
	SelectObject(hBufDC, OldBitmap);
	DeleteDC(hBufDC);
	SelectObject(hCardDC, OldBitmap2);
	DeleteObject(hCardDC);
}

HBITMAP DrawCard::GetDoubleBuffer(void)
{
	return hDBuff;
}

void DrawCard::DrawBackground(HDC hDC)
{
	HDC hBufDC;
	HBITMAP OldBitmap;
	HBRUSH OldBrush;
	HPEN OldPen;
	RECT rect;
	unsigned int cnt;

	hBufDC = CreateCompatibleDC(hDC);
	OldBitmap = (HBITMAP)SelectObject(hBufDC, hDBuff);
	OldBrush = (HBRUSH)SelectObject(hBufDC, BackgroundBrush);
	OldPen = (HPEN)SelectObject(hBufDC, GetStockObject(NULL_PEN));
	GetClientRect(hWnd, &rect);
	Rectangle(hBufDC, rect.left, rect.top, rect.right, rect.bottom);

	SelectObject(hBufDC, OldPen);
	Rectangle(hBufDC, DECK_RIGHT_X, DECK_RIGHT_Y, DECK_RIGHT_X + CARD_WIDTH, DECK_RIGHT_Y+CARD_HEIGHT);
	for (cnt = 0; cnt < 4; cnt++)
	{
		Rectangle(hBufDC, HOMESTACK_X(cnt), HOMESTACK_Y, HOMESTACK_X(cnt) + CARD_WIDTH, HOMESTACK_Y+CARD_HEIGHT);
		Rectangle(hBufDC, COLUMN_X(cnt), COLUMN_Y, COLUMN_X(cnt) + CARD_WIDTH, COLUMN_Y+CARD_HEIGHT);
	}
	for (; cnt < 7; cnt++)
	{
		Rectangle(hBufDC, COLUMN_X(cnt), COLUMN_Y, COLUMN_X(cnt) + CARD_WIDTH, COLUMN_Y + CARD_HEIGHT);
	}

	SelectObject(hBufDC, OldBrush);
	SelectObject(hBufDC, OldBitmap);
	DeleteDC(hBufDC);
}
