#include <Windows.h>

LPCWSTR g_szClassName = L"myWindowClass";

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_LBUTTONDOWN:
	{
		TCHAR szFileName[MAX_PATH];
		HINSTANCE hInstance = GetModuleHandle(NULL);
		GetModuleFileNameW(hInstance, szFileName, MAX_PATH);
		MessageBox(hwnd, szFileName, L"This program is:", MB_OK | MB_ICONINFORMATION);
	}
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Register the window class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBoxA(NULL, "WINDOW REG FAILED", "ERROR!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//Create the window
	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		L"TITLE OF MY WINDOW",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL); \

		if (hwnd == NULL) {
			MessageBoxA(NULL, "WINDOW CREATION FAILED", "ERROR!", MB_ICONEXCLAMATION | MB_OK);
			return 0;
		}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//Message Loop
	while (GetMessage(&Msg, NULL, 0, 0) > 0) {
		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}
	return Msg.wParam;
}
