#include "StatusBar.h"


StatusBar::StatusBar(HWND aWnd)
{
	RECT rect;

	this->hWnd = aWnd;
	InitCommonControls();
	this->hState = CreateStatusWindow(WS_CHILD | WS_VISIBLE, TEXT("Status Line"), hWnd, 0);
	memset(strInfo, 0, 128);
	uiScore = 0;
	uiTime = 0;
	GetClientRect(hWnd, &rect);
	SizeChanged(0, rect.right);
}

StatusBar::~StatusBar()
{
}

void StatusBar::SizeChanged(WPARAM wParam, LPARAM lParam)
{
	int SBPart[3];

	SendMessage(hState, WM_SIZE, 0, 0);

	SBPart[0] = LOWORD(lParam) * 2 / 3;
	SBPart[1] = SBPart[0] + LOWORD(lParam) / 6;
	SBPart[2] = LOWORD(lParam);

	SendMessage(hState, SB_SETPARTS, 3, (LPARAM)SBPart);

	SetStatusText();
}

void StatusBar::SetStatusText(void)
{
	TCHAR strBuff[128] = { 0, };

	SendMessage(hState, SB_SETTEXT, 0, (LPARAM)strInfo);
	wsprintf(strBuff, L"Score: %d", uiScore);
	SendMessage(hState, SB_SETTEXT, 1, (LPARAM)strBuff);
	wsprintf(strBuff, L"Time: %d", uiTime);
	SendMessage(hState, SB_SETTEXT, 2, (LPARAM)strBuff);
}

void StatusBar::SetInfo(TCHAR * info)
{
	lstrcpy(strInfo, info);
	SetStatusText();
}

void StatusBar::SetScore(UINT32 score)
{
	this->uiScore = score;
	SetStatusText();
}

void StatusBar::SetTime(UINT32 time)
{
	this->uiTime = time;
	SetStatusText();
}

void StatusBar::GetArea(RECT * rect)
{
	SendMessage(hState, SB_GETRECT, NULL, (LPARAM)rect);
}
