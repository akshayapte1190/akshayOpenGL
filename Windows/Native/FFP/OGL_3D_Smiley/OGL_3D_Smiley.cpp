#include<Windows.h>
#include<stdio.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#include "resource.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
static float angle;
GLuint texture_smiley;
HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
FILE *gpFile = NULL;
bool gbFullScreen = false;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
int pressedDigit = 0;
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	int iRet = 0;
	bool bDone = false;

	TCHAR szAppName[] = TEXT("OGL_3D_Smiley");

	int initialize(void);
	void display(void);
	void update(void);

	if (fopen_s(&gpFile, "OGL_3D_Smiley.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("File not created"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "File Created Successfully for Double Buffer with Trangle\n");
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("OGL_3D_Smiley"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("Window is not created"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}

	ghwnd = hwnd;

	iRet = initialize();

	if (iRet == -1)
	{
		fprintf(gpFile, "Choose Pixel Format error\n");
		exit(0);
	}
	else if (iRet == -2)
	{
		fprintf(gpFile, "Error in Set pixel format\n");
		exit(0);
	}
	else if (iRet == -3)
	{
		fprintf(gpFile, "wglMakeCurrent Failed");
		exit(0);
	}
	else
	{
		fprintf(gpFile, "initialize function successful\n");
	}
	ShowWindow(hwnd, nCmdShow);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);

	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{

			}
			display();
			update();
		}
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	void ToggleFullScreen(void);
	void reshape(int, int);
	void uninitialize(void);

	switch (iMsg)
	{

	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case 49:
		case VK_NUMPAD1:
			pressedDigit = 1;
			break;

		case 50:
		case VK_NUMPAD2:
			pressedDigit = 2;
			break;

		case 51:
		case VK_NUMPAD3:
			pressedDigit = 3;
			break;

		case 52:
		case VK_NUMPAD4:
			pressedDigit = 4;
			break;

		case VK_ESCAPE:
			DestroyWindow(hwnd);

		case 0x46:
			ToggleFullScreen();
			break;
		default:
			pressedDigit = 0;
			break;
		}
		break;

	case WM_SIZE:
		reshape(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;

	case WM_DESTROY:
		uninitialize();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}

int initialize()
{
	void reshape(int, int);
	BOOL LoadTexture(GLuint *, TCHAR[]);
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		return -1;
	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return -2;
	}

	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		return -3;
	}

	if (wglMakeCurrent(ghdc, ghrc) == NULL)
	{
		return -4;
	}
	glShadeModel(GL_SMOOTH);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	LoadTexture(&texture_smiley, MAKEINTRESOURCE(IDSMIELY));
	reshape(WIN_WIDTH, WIN_HEIGHT);

	return(0);

}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);

		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);

		ShowCursor(true);
	}

	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}

	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	if (gpFile)
	{
		fprintf(gpFile, "File Closed Successfully\n");
		fclose(gpFile);
		gpFile = NULL;
	}
	glDeleteTextures(1, &texture_smiley);
}


void reshape(int width, int height)
{
	//code added
	if (height == 0)
	{
		height = 1;
	}
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0f, (GLfloat)width / (GLfloat)height, 0.5f, 100.0f);
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-2.0f, 0.0f, -10.0f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	if (pressedDigit == 1)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-2.0f, 0.0f, -10.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);

		glBindTexture(GL_TEXTURE_2D, texture_smiley);
		glBegin(GL_QUADS);
		glTexCoord2f(0.5f, 0.5f);
		glVertex2f(0.5f, 0.5f);
		glTexCoord2f(0.0f,0.5f);
		glVertex2f(-0.5f, 0.5f);
		glTexCoord2f(0.0f,0.0f);
		glVertex2f(-0.5f, -0.5f);
		glTexCoord2f(0.5f,0.0f);
		glVertex2f(0.5f, -0.5f);
		glEnd();
	}

	else if (pressedDigit == 2)
	{
		
		glBindTexture(GL_TEXTURE_2D, texture_smiley);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(-2.0f, 0.0f, -10.0f);
		glRotatef(angle, 0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);

		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glEnd();

		//Bottom
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1.0f, 0.0f, -15.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();


		//Front
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1.0f, 0.0f, -15.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glEnd();


		//Back
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1.0f, 0.0f, -15.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();

		//Right
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1.0f, 0.0f, -15.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glEnd();

		//Left
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(1.0f, 0.0f, -15.0f);
		glRotatef(angle, 1.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glEnd();
	}

	else if (pressedDigit == 3)
	{
	glBindTexture(GL_TEXTURE_2D, texture_smiley);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(0.35f, 0.35f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.35f, 0.65f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(0.65f, 0.65f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(0.65f, 0.35f, 0.0f);
	glEnd();

	}


	else if (pressedDigit == 4)
	{
	glBindTexture(GL_TEXTURE_2D, texture_smiley);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	}
	else
	{
	
	glBindTexture(GL_TEXTURE_2D, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 1.0f);
	
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	//Bottom
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();


	//Front
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();


	//Back
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	//Right
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	//Left
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.0f, 0.0f, -15.0f);
	glRotatef(angle, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f,1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(0.0f,1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0f,0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
	}
	SwapBuffers(ghdc);
}

void ToggleFullScreen()
{
	MONITORINFO mi;
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);

		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			mi = { sizeof(MONITORINFO) };

			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle &~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);

			}
		}

		ShowCursor(false);
		gbFullScreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(false);
		gbFullScreen = false;
	}


}
void update(void)
{
	angle = angle + 0.1f;
	if (angle >= 360.0f)
		angle = 0.0f;
}

BOOL LoadTexture(GLuint *texture, TCHAR imageResourceID[])
{
	HBITMAP hBitmap = NULL;
	BITMAP bmp;
	BOOL bStatus = FALSE;



	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), imageResourceID, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

	if (hBitmap)
	{
		bStatus = TRUE;
		GetObject(hBitmap, sizeof(BITMAP), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glGenTextures(1, texture);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);


		DeleteObject(hBitmap);
	}
	return bStatus;
}
