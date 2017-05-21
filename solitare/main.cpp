#include <Windows.h>
#include <string>
#include <iostream>
#include "Solitaire.h"
#include "resource.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EndDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
void CALLBACK GameTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
LPCTSTR lpszClass = TEXT("Solitaire");
HWND hWnd;
HINSTANCE g_hInst;
Solitaire * game;
bool bButtonOn = false;
unsigned int old_x, old_y;
unsigned int cur_x, cur_y;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	HACCEL hAccel;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	hAccel = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATOR1));
	while (GetMessage(&Message, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &Message))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	RECT rect;
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP OldBitmap;
	CardLocation axis;

	switch (iMessage)
	{
	case WM_CREATE:
		game = new Solitaire(g_hInst, hWnd, GameTimer);
		return 0;
	case WM_GETMINMAXINFO:
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WINDOW_WIDTH;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WINDOW_HEIGHT;
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WINDOW_WIDTH;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WINDOW_HEIGHT;
	case WM_SIZE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_NEWGAME:
			if (IDOK == MessageBox(hWnd, TEXT("게임을 다시 시작하시겠습니까?"), TEXT("New Game"), MB_ICONQUESTION|MB_OKCANCEL))
			{
				delete game;
				game = new Solitaire(g_hInst, hWnd, GameTimer);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			return 0;
		case ID_UNDO:
			if (game->CardBack() == false)
			{
				game->GameInfo(TEXT("Warning: UNDO FAIL"));
			}
			else
			{
				game->DrawAll(hWnd);
			}
			return 0;
		case ID_EXIT:
			if (IDOK == MessageBox(hWnd, TEXT("게임을 종료하시겠습니까?"), TEXT("Exit"), MB_ICONQUESTION|MB_OKCANCEL))
			{
				delete game;
				PostQuitMessage(0);
			}
			return 0;
		}
		return 0;
	case WM_RBUTTONDOWN:
		return 0;
	case WM_LBUTTONDBLCLK:
		axis = game->TranslateAxis(LOWORD(lParam), HIWORD(lParam));
		game->CardDoubleClick(axis, HIWORD(lParam));
		game->DrawAll(hWnd);
		return 0;
	case WM_LBUTTONDOWN:
		if (bButtonOn)
		{
			SendMessage(hWnd, WM_LBUTTONUP, wParam, lParam);
			return 0;
		}
		axis = game->TranslateAxis(LOWORD(lParam), HIWORD(lParam));
		if (game->CardDown(axis, LOWORD(lParam), HIWORD(lParam)))
		{
			bButtonOn = true;
			cur_x = LOWORD(lParam);
			cur_y = HIWORD(lParam);
			game->UpdateCardAxis(LOWORD(lParam), HIWORD(lParam));
			game->DrawAll(hWnd);
		}
		game->GameInfo(TEXT("Playing..."));
		return 0;
	case WM_LBUTTONUP:
		if (bButtonOn)
		{
			bButtonOn = false;
			axis = game->TranslateAxis(LOWORD(lParam), HIWORD(lParam));
			game->CardUp(axis, HIWORD(lParam));
			game->UpdateCardAxis(0, 0);
			game->DrawAll(hWnd);
		}
		if (game->IsGameRunning())
		{
			if (game->IsGameComplete())
			{
				game->GameStop(hWnd);
				if (IDOK == DialogBox(g_hInst, MAKEINTRESOURCE(IDD_END_DIALOG), hWnd, EndDialogProc))
				{
					delete game;
					game = new Solitaire(g_hInst, hWnd, GameTimer);
					InvalidateRect(hWnd, NULL, TRUE);
				}
			}
		}
		return 0;
	case WM_MOUSEMOVE:
		if (bButtonOn)
		{
			old_x = cur_x, old_y = cur_y;
			cur_x = LOWORD(lParam), cur_y = HIWORD(lParam);
			game->UpdateCardAxis(LOWORD(lParam), HIWORD(lParam));
			game->DrawAll(hWnd);
		}
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (game != NULL)
		{
			MemDC = CreateCompatibleDC(hdc);
			GetClientRect(hWnd, &rect);
			//MyBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_CARD));
			OldBitmap = (HBITMAP)SelectObject(MemDC, game->GetDoubleBuffer());
			BitBlt(hdc, 0, 0, rect.right, rect.bottom, MemDC, 0, 0, SRCCOPY);
			SelectObject(MemDC, OldBitmap);
			DeleteDC(MemDC);
		}
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		delete game;
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

INT_PTR CALLBACK EndDialogProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, IDC_SCORE, game->Score, FALSE);
		SetDlgItemInt(hDlg, IDC_TIME, game->Time, FALSE);
		return true;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hDlg, IDOK);
			return true;
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			return true;
		}
		break;
	}
	return false;
}


void CALLBACK GameTimer(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (game != NULL)
	{
		game->GameTime();
	}
}