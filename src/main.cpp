#define UNICODE
#define _UNICODE
#define WINVER 0x0600
#include <windows.h>
#include <wingdi.h>
#include <tchar.h>
#include <time.h>

#include "life.h"

const int scale = 4;
const int grid_width = 201;
const int grid_height = 101;
const int real_width  = grid_width * scale;
const int real_height = grid_height * scale;

//#define MINE_TIMER
#ifdef  MINE_TIMER
const int frames = 10/100;
#else
	// Horrible piece of shit (hello linux core developers)
	#ifndef USER_TIMER_MINIMUM
	#define USER_TIMER_MINIMUM 0x0000000A
	#endif
#endif

tlife* life;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdStr, int nCmdShow) {
	srand(time(NULL));
    // create window class and clean memory for it =)
    WNDCLASSEX wc;
    ZeroMemory(& wc, sizeof(WNDCLASSEX));

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc; // procedure that process messages
    wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("SomeHelloClass");

    RegisterClassEx(& wc);

    HWND hwnd = CreateWindowEx(0, //
        wc.lpszClassName, // name of window class
        _T("Life with MinGW && VIM|Notepad++"), // window->caption
        WS_OVERLAPPEDWINDOW, // style of window
        CW_USEDEFAULT, CW_USEDEFAULT, // x,y
        real_width+20, real_height+50, // // width, height
        NULL, // parent HWND
        NULL, // menu
        hInstance, NULL // lParam
        );

    ShowWindow(hwnd, SW_SHOW);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(& msg);
        DispatchMessage(& msg);
    }

    return (int)msg.wParam;
}

HBITMAP bmp;

int PaintProc(HWND hWnd) {
	static const lType** grid = life->get_grid();
	static HBRUSH foreground = CreateSolidBrush(RGB(255,0,0));
	static HBRUSH background = CreateSolidBrush(RGB(0,0,0));

	PAINTSTRUCT ps;
	RECT clrect;

    HDC hdc = GetDC(hWnd);
	
	GetClientRect(hWnd, &clrect);

    HDC memDC = CreateCompatibleDC ( hdc );
    HBITMAP memBM = CreateCompatibleBitmap (hdc, grid_height, grid_width);
	SelectObject ( memDC, memBM );
	
	clrect.left = clrect.top = 0;
	clrect.right = real_width;
	clrect.bottom = real_height;
	FillRect(memDC, &clrect, background);
	
	for (int y = 0; y < grid_height; ++y)
		for (int x = 0; x < grid_width; ++x)
			if (grid[y][x]) {
				const COLORREF color = RGB(255,255,0);
				SetPixel(memDC, x, y, color);
			}
			
	//BitBlt(hdc,0,0,grid_height,grid_width,memDC,0,0,SRCCOPY);
	StretchBlt(hdc,0,0,real_width,real_height,memDC,0,0,grid_width,grid_height,SRCCOPY);
	ReleaseDC(hWnd, hdc);

	// Sleep(0);
	life->step();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int nTimerID;
	switch (message) {
	case WM_CREATE: {
#ifdef MINE_TIMER
			nTimerID = SetTimer(hWnd, 1, frames, (TIMERPROC) NULL);
#else
			nTimerID = SetTimer(hWnd, 1, USER_TIMER_MINIMUM, (TIMERPROC) NULL);
#endif
			life = new tlife(grid_width,grid_height);
			life->seed(grid_width*grid_height/3);
			return 0;
		} break;
	case WM_TIMER: {
			//SendMessage(hWnd, WM_PAINT, 0, 0);
			PaintProc(hWnd);
			RedrawWindow(hWnd , NULL , NULL , RDW_INVALIDATE);
			Sleep(0);
			return 0;		
		} break;
    case WM_PAINT: {
			// return PaintProc(hWnd);
		} break;
    case WM_DESTROY: {
			delete life;
			KillTimer(hWnd, 1);
			PostQuitMessage(0);
            return 0;
        } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}
