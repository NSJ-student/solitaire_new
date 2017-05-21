#pragma once
#include "Card.h"
#include "CardDeque.h"
#include "Deck.h"
#include "HomeStack.h"
#include "Column.h"
#include <Windows.h>

#define CARD_HEIGHT			96
#define CARD_WIDTH			71
#define HIDDEN_CARD_GAP		5
#define EXPOSED_CARD_GAP	25
#define SIDE_CARD_GAP_W		30
#define SIDE_CARD_GAP_H		20

#define WINDOW_WIDTH		(7*CARD_WIDTH + 8*SIDE_CARD_GAP_W)
#define WINDOW_HEIGHT		(SIDE_CARD_GAP_H*2 + CARD_HEIGHT*5)

#define DECK_LEFT_X		SIDE_CARD_GAP_W
#define DECK_LEFT_Y		SIDE_CARD_GAP_H

#define DECK_RIGHT_X		(SIDE_CARD_GAP_W*2+CARD_WIDTH)
#define DECK_RIGHT_Y		SIDE_CARD_GAP_H

#define HOMESTACK_X(x)			(SIDE_CARD_GAP_W*(4+x) + CARD_WIDTH*(3+x))
#define HOMESTACK_Y				SIDE_CARD_GAP_H

#define COLUMN_X(x)			(SIDE_CARD_GAP_W*(1+x) + CARD_WIDTH*(x))
#define COLUMN_Y				(SIDE_CARD_GAP_H*2+CARD_HEIGHT)

class DrawCard
{
private:
	HINSTANCE hInstance;
	HWND hWnd;
	HBRUSH BackgroundBrush, CardBrush;
	HBITMAP hDBuff;			// 더블 버퍼링
	HBITMAP hCardBitmap;	// 카드 그림
public:
	DrawCard(HINSTANCE instance, HWND wnd);
	~DrawCard();
	void Init(HINSTANCE instance, HWND wnd);
	void DrawMovingCard(HDC hDC, Card * card, unsigned int x, unsigned int y);
	void DrawDeck(HDC hDC, Deck * Deck);
	void DrawHomeStack(HDC hDC, HomeStack * HomeStack, unsigned int position);
	void DrawColumn(HDC hDC, Column * Column, unsigned int position);
	HBITMAP  GetDoubleBuffer(void);
	void DrawBackground(HDC hDC);
};

