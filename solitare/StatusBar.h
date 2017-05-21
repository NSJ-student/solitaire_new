#ifndef __STATUSBAR_H__
#define __STATUSBAR_H__

#include <Windows.h>
#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <String>
using namespace std;

class StatusBar
{
private:
	HWND hWnd;
	HWND hState;
	TCHAR strInfo[128];
	UINT32 uiScore;
	UINT32 uiTime;
public:
	StatusBar(HWND aWnd);
	~StatusBar();
	void SizeChanged(WPARAM wParam, LPARAM lParam);
	void SetStatusText(void);
	void SetInfo(TCHAR * info);
	void SetScore(UINT32 score);
	void SetTime(UINT32 time);
	void GetArea(RECT * rect);
};

#endif // __STATUSBAR_H__