#pragma once
#include "includes.h"

#define IS_INSIDE_CARD(x, y, deck_x, deck_y)		((x > deck_x) && (x < deck_x + CARD_WIDTH) &&	\
													(y > deck_y) && (y < deck_y + CARD_HEIGHT))
#define IS_INSIDE_CARDC(x, y, deck_x, deck_y, w, h)	((x > deck_x) && (x < deck_x + w) &&	\
													(y > deck_y) && (y < deck_y + h))
#define IS_IN_THIS_AREA(loc, from, to)				((loc >= from) && (loc <= to))

typedef enum card_locate {
	NOTHING,
	DECK_STACK,
	DECK_VISIBLE,
	HOMESTACK1, HOMESTACK2, HOMESTACK3, HOMESTACK4,
	COLUMN1, COLUMN2, COLUMN3, COLUMN4, COLUMN5, COLUMN6, COLUMN7
} CardLocation;

#define SCORE_DECK_TO_COLUMN	5
#define SCORE_TO_HOME_STACK		10

class Solitaire
{
private:
	CardStack * Stack;
	Deck * Pile;
	HomeStack * Foundation[4];
	Column * Tableau[7];

	CardDeque * PrevDeck;

	DrawCard * Draw;
	StatusBar * Status;

	unsigned int m_card_x, m_card_y;
	unsigned int offset_x, offset_y;
	bool bRun;
public:
	unsigned int Score;
	unsigned int Time;
	Card * MovingCard;

	Card * MovedCard;
	CardDeque * MovedDeck_From;
	CardDeque * MovedDeck_To;

	Solitaire(HINSTANCE hInstance, HWND hWnd, TIMERPROC tProc);
	~Solitaire();


	void DrawAll(HWND hWnd);
	HBITMAP GetDoubleBuffer(void);

	bool CardDown(CardLocation location, unsigned int axis_x, unsigned int axis_y);
	bool CardUp(CardLocation location, unsigned int axis_y);
	bool CardDoubleClick(CardLocation location, unsigned int axis_y);
	bool CardBack(void);

	CardLocation TranslateAxis(unsigned int x, unsigned int y);
	void UpdateCardAxis(unsigned int x, unsigned int y);

	bool IsGameComplete(void);

	void GameInfo(TCHAR * info);
	void GameScore(int scr);
	void GameTime(void);

	void GameStop(HWND hWnd);
	bool IsGameRunning(void);
};

