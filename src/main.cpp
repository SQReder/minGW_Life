#define UNICODE
#define _UNICODE
#include <windows.h>
#include <wingdi.h>
#include <tchar.h>
#include <time.h>

#include "life.h"

#define scale 4
#define w 201
#define h 201
const int frames = 10/100;

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
        w*scale+20, h*scale+50, // // width, height
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
	// FillRect(hdc, &clrect, (HBRUSH)COLOR_WINDOW);

    HDC memDC = CreateCompatibleDC ( hdc );
    HBITMAP memBM = CreateCompatibleBitmap (hdc, h, w);
	SelectObject ( memDC, memBM );
	
	clrect.left = clrect.top = 0;
	clrect.right = w * scale;
	clrect.bottom = h * scale;
	FillRect(memDC, &clrect, background);
	
	for (int y = 0; y < h; ++y)
		for (int x = 0; x < w; ++x)
			if (grid[y][x]) {
				// RECT r;
				// r.left = x*scale;
				// r.right = x*scale+scale;
				// r.top = y*scale;
				// r.bottom = y*scale+scale;
				// FillRect(memDC, &r, foreground);
				const COLORREF color = RGB(255,255,0);
				SetPixel(memDC, x, y, color);
			}
			
	// BitBlt(hdc,0,0,h,w,memDC,0,0,SRCCOPY);
	StretchBlt(hdc,0,0,w*scale,h*scale,memDC,0,0,w,h,SRCCOPY);
	ReleaseDC(hWnd, hdc);

	// Sleep(0);
	life->step();
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static int nTimerID;
	switch (message) {
	case WM_CREATE: {
			nTimerID = SetTimer(hWnd, 1, frames, (TIMERPROC) NULL);
			life = new tlife(w,h);
			life->seed(w*h/3);
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
