#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Test");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);


	RegisterClassEx(&wndclass);


	hwnd = CreateWindow(szAppName, TEXT("Test Win32"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, hInstance, NULL);


	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);


	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case 'F':
			MessageBox(NULL, TEXT("Capital F if pressed"), TEXT("F"), MB_OK | MB_ICONINFORMATION);
			break;
		case 'f':
			MessageBox(NULL, TEXT("Small f is pressed"), TEXT("f"), MB_OK | MB_ICONINFORMATION);
			break;
		case VK_ESCAPE:
			MessageBox(NULL, TEXT("Escape key is pressed...Existing from Window"), TEXT("Good Bye"), MB_OKCANCEL | MB_ICONINFORMATION);
			DestroyWindow(hwnd);
			break;

		case VK_RETURN:
			MessageBox(hwnd, TEXT("Enter key is pressed"), TEXT("Enter"), MB_OK|MB_ICONINFORMATION);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
