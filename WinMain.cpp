#include"define.h"

HINSTANCE g_hInst;
LPCTSTR lpszClass = WIN_TITLE;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	srand((unsigned)time(NULL));

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;


	DWORD dwStyle = WS_OVERLAPPEDWINDOW | WS_SYSMENU;

	RECT rcWindow{};
	GetWindowRect(GetDesktopWindow(), &rcWindow);	// GetDesktopWindow() - 데스크탑의 해상도

	RECT rcClient{ 0,0,CLIENT_WIDTH,CLIENT_HEIGHT };
	AdjustWindowRect(&rcClient, dwStyle, false);

	rcClient.right -= rcClient.left;				// 윈도우에서 실제 작업 창을 정한 크기대로 설정해줌
	rcClient.bottom -= rcClient.top;
	rcClient.left = rcClient.top = 0;

	LONG xStart = (rcWindow.right - rcClient.right) / 2;
	LONG yStart = (rcWindow.bottom - rcClient.bottom) / 2;

	g_hInst = hInstance;

	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&WndClass);


	hWnd = CreateWindow(lpszClass
		, WIN_TITLE
		, dwStyle

		, xStart
		, yStart
		, rcClient.right
		, rcClient.bottom

		, NULL
		, (HMENU)NULL
		, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}

void WMPaint(HDC);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (iMessage) {
	case WM_CREATE:
		SetTimer(hWnd, WT_UPDATE, UPDATE_FPS, NULL);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		HDC memdc = CreateCompatibleDC(hdc);
		HBITMAP memBit = CreateCompatibleBitmap(hdc, CLIENT_WIDTH, CLIENT_HEIGHT);
		SelectObject(memdc, memBit);
		Rectangle(memdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT);
		WMPaint(memdc);
		BitBlt(hdc, 0, 0, CLIENT_WIDTH, CLIENT_HEIGHT, memdc, 0, 0, SRCCOPY);
		DeleteDC(memdc);
		DeleteObject(memBit);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_TIMER:
		switch (wParam) {
		case WT_UPDATE:
			InvalidateRect(hWnd, NULL, FALSE);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void WMPaint(HDC hdc)
{

}
