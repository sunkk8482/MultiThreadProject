#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ThreadFunc(LPVOID prc);
void DoCreateMain(HWND hWnd);
void DoButtonMain(HWND hWnd);
void DoPaintMain(HWND hWnd);
void OnTimer(HWND hWnd);
COPYDATASTRUCT* pcds;
#define R 20
#define BOUNCE 1
#define W 20
#define H 200

HBITMAP hBit;
HINSTANCE g_hInst;
HWND hWndMain, hWnd2;
HANDLE hThread;
LPCTSTR lpszClass = TEXT("Bounce"); // ������â�� ����

RECT crt;
int x, y;
int xv, yv;
int flag = 0;
int btnflag = 0;


struct trans_struct {
	int x;
	int y;
	int xv;
	int yv;
}trans_struct;

void moveStick();
void moveBall();
void collision();

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

	//���ø�
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_BORDER | WS_CAPTION | WS_SYSMENU,
		CW_USEDEFAULT, CW_USEDEFAULT, 400, 600,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
int start = 0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	//���Ⱑ �ݺ������� ���ư�
	//windows�� messege driven os�̴�

	struct trans_struct my;
	my.x = x;
	my.y = y;
	my.xv = xv;
	my.yv = yv;
	HWND hWnd1 = NULL;
	HWND hWnd3 = NULL;
	COPYDATASTRUCT cds;


	if (x > 0 && x < 370)
	{
		start = 1;
	}
	else
	{
		start = 0;
	}



	switch (iMessage) {

	case WM_CREATE:
		DoCreateMain(hWnd);
		break;
	case WM_PAINT:
		DoPaintMain(hWnd);
		cds.cbData = sizeof(my);
		cds.dwData = 0;
		cds.lpData = &my;
		hWnd1 = FindWindow(NULL, L"Bounce2");
		if(hWnd1!=NULL)
			SendMessage(hWnd1, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
		hWnd3 = FindWindow(NULL, L"Bounce3");
		if (hWnd3 != NULL)
			SendMessage(hWnd3, WM_COPYDATA, (WPARAM)hWnd, (LPARAM)&cds);
		break;
	case WM_LBUTTONDOWN: //���콺 ���ʹ�ư�� ��������
		DoButtonMain(hWnd); // �� �Լ� ����
		break;
	case WM_TIMER: //Ÿ�̸Ӹ� �߻�
		OnTimer(hWnd);
		break;
	case WM_DESTROY: // ���α׷� ��
		PostQuitMessage(0);
		KillTimer(hWnd, 0);
		CloseHandle(hThread);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void DoCreateMain(HWND hWnd)
{
	GetClientRect(hWnd, &crt);

	x = 80;	//���� x ��ǥ �ʱⰪ
	y = 250;//���� y ��ǥ �ʱⰪ

	xv = (rand() % 4) + 5; //x���� �ӵ�
	yv = (rand() % 4) + 5; //y���� �ӵ�

}

void DoPaintMain(HWND hWnd)
{
	HDC hdc, hMemDC;
	PAINTSTRUCT ps;
	HBITMAP OldBit;

	hdc = BeginPaint(hWnd, &ps);

	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);
	BitBlt(hdc, 0, 0, crt.right, crt.bottom, hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	EndPaint(hWnd, &ps);
	return;
}

void DoButtonMain(HWND hWnd)
{
	if (btnflag == 0) {
		MessageBox(hWnd, TEXT("���α׷��� ����Ǿ����ϴ�."), TEXT("OK"), MB_OK);
		SetTimer(hWnd, 1, 25, NULL);
	}
	if (btnflag > 0) { //���α׷� ������
		flag = 0;
	}
	btnflag = 1;

}

void OnTimer(HWND hWnd)
{
	TCHAR str[123];
	HDC hdc, hMemDC;
	HBITMAP OldBit;
	HPEN hPen, OldPen;
	HBRUSH hBrush, OldBrush;

	hdc = GetDC(hWnd);
	GetClientRect(hWnd, &crt);
	if (hBit == NULL)
	{
		hBit = CreateCompatibleBitmap(hdc, crt.right, crt.bottom);
	}
	hMemDC = CreateCompatibleDC(hdc);
	OldBit = (HBITMAP)SelectObject(hMemDC, hBit);

	FillRect(hMemDC, &crt, GetSysColorBrush(COLOR_WINDOW));

	hPen = CreatePen(PS_INSIDEFRAME, 2, RGB(0, 0, 0));
	OldPen = (HPEN)SelectObject(hMemDC, hPen);
	hBrush = CreateSolidBrush(RGB(255, 120, 0));
	OldBrush = (HBRUSH)SelectObject(hMemDC, hBrush);
	Ellipse(hMemDC, x - R, y - R, x + R, y + R);	 //���׸���


	DeleteObject(SelectObject(hMemDC, OldPen));
	DeleteObject(SelectObject(hMemDC, OldBrush));

	if (start ==1) {
		wsprintf(str, TEXT("%d, %d, %d, %d"), x, y, xv, yv);
	}
	else if (start == 0)
	{
		wsprintf(str, TEXT("%d, %d, %d, %d"), 0, 0, 0, 0);
	}
	
	TextOut(hMemDC, 100, 50, str, lstrlen(str));

	SelectObject(hMemDC, OldBit);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hdc);
	InvalidateRect(hWnd, NULL, FALSE);

	moveBall();  //���� ������
	collision();



}

void moveBall()
{
	if (y <= R || y >= crt.bottom - R) {
		yv *= -(BOUNCE);
		if (y <= R) y = R;
		if (y >= crt.bottom - R) y = crt.bottom - R;
	}
	x += (int)xv;
	y += (int)yv;

}

void collision()
{
	if (flag == 0)
	{

		if (x < W + R)
		{
			x += R / 2;
			xv *= (-BOUNCE);
		}
		if (x >= crt.right+800 - R - W)
		{
			x -= R / 2;
			xv *= (-BOUNCE);
		}
	}

}

