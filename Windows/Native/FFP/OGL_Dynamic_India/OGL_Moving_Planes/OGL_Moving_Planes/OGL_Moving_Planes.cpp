#include<Windows.h>
#include<stdio.h>
#include<GL/GL.h>
#include<GL/GLU.h>
#define _USE_MATH_DEFINES 1
#include<math.h>

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#define WIN_WIDTH 700
#define WIN_HEIGHT 700
#define NUM_POINTS 1000
HDC ghdc = NULL;
HWND ghwnd = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
FILE *gpFile = NULL;
bool gbFullScreen = false;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	int iRet = 0;
	bool bDone = false;

	TCHAR szAppName[] = TEXT("Moving India Letters");

	int initialize(void);
	void display(void);

	if (fopen_s(&gpFile, "Moving_India_Letters.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("File not created"), TEXT("Error"), MB_OK | MB_ICONERROR);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "File Created Successfully for InCircle\n");
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

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("OGL_Moving_India_Letters"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);

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
	case WM_CREATE:
		ToggleFullScreen();
		break;
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);

		case 0x46:
			ToggleFullScreen();
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
	void ToggleFullScreen();
	void reshape(int, int);

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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	reshape(WIN_WIDTH, WIN_HEIGHT);
	ToggleFullScreen();
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
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.5f, 100.0f);


}

void display(void)
{

	static GLfloat xAxisPlaneMiddle = -5.8f,xAxisForColor=-1.0f,rColor1=0.9f,gColor1=0.9f,bColor1=0.9f,
		rColor2 = 0.9f, gColor2 = 0.9f, bColor2 = 0.9f,
		rColor3 = 0.9f, gColor3 = 0.9f, bColor3 = 0.9f;
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlaneMiddle, 0.0f, 0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glLineWidth(6.0f);
	glColor3f(176.0f / 255.0f, 224.0f / 255.0f, 230.0f / 255.0f);
	//1st plane
	glBegin(GL_LINES);
	glVertex2f(0.0f,0.0f);
	glVertex2f(0.8f,0.0f);

	glVertex2f(0.8f,0.0f);
	glVertex2f(1.3f,-0.2f);


	glVertex2f(1.3f,-0.2f);
	glVertex2f(0.0f,-0.2f);

	glVertex2f(0.018f, 0.0f);
	glVertex2f(0.018f,-0.2f);



	glEnd();

	//1st Quads for 1st plane
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlaneMiddle, 0.0f, 0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glColor3f(176.0f / 255.0f, 224.0f / 255.0f, 230.0f / 255.0f);
	glBegin(GL_QUADS);
	glVertex2f(0.2f, 0.0f);
	glVertex2f(0.2f, 0.3f);

	glVertex2f(0.2f, 0.3f);
	glVertex2f(0.5f, 0.35f);

	glVertex2f(0.5f, 0.35f);
	glVertex2f(0.7f, 0.0f);

	glVertex2f(0.7f, 0.0f);
	glVertex2f(0.2f,0.0f);
	glEnd();

	//2nd Quads for 1st Plane

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlaneMiddle,0.0f,0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glColor3f(176.0f / 255.0f, 224.0f / 255.0f, 230.0f / 255.0f);
	glBegin(GL_QUADS);

	glVertex2f(0.23f,-0.2f);
	glVertex2f(0.23f,-0.48f);
	glVertex2f(0.6f,-0.6f);
	glVertex2f(0.7f, -0.2f);

	glEnd();
	////IAF Letter
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glLineWidth(1.8f);
	////glTranslatef(0.33f,-0.15f,0.0f);
	//gluLookAt(0, 0, 6, 0, 0, 0, 0, 1, 0);
	//glColor3f(1.0f, 1.0f, 1.0f);
	//glBegin(GL_LINES);
	////I Letter
	//glVertex2f(0.15f,-0.03f);
	//glVertex2f(0.15f,-0.17f);

	////A Letter
	//glVertex2f(0.22f, 0.1f);
	//glVertex2f(0.19f,0.0f);
	//glVertex2f(0.22f, 0.1f);
	//glVertex2f(0.25f,0.0f);
	//glVertex2f(0.20f, 0.04f);
	//glVertex2f(0.24f, 0.04f);

	////F Letter
	//glVertex2f(0.28f,0.1f);
	//glVertex2f(0.28f,0.0f);

	//glVertex2f(0.28f,0.10f);
	//glVertex2f(0.33f, 0.10f);

	//glVertex2f(0.28f, 0.04f);
	//glVertex2f(0.33f, 0.04f);
	//glEnd();

	xAxisPlaneMiddle = xAxisPlaneMiddle + 0.001f;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlaneMiddle, 0.0f, 0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glColor3f(255.0f/255.0f, 153.0f / 255.0f, 51.0f / 255.0f);//Saffron Color
	if (xAxisPlaneMiddle >= 6.5f)
	{
		glColor3f(rColor1, gColor1, bColor1);
		rColor1 = rColor1 - 0.001f;
		gColor1 = gColor1 - 0.001f;
		bColor1 = bColor1 - 0.001f;

	}
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex2f(xAxisForColor, 0.0f);
	glVertex2f(0.0f, 0.0f);
	glEnd();
	xAxisForColor = xAxisForColor - 0.0001f;


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlane, 0.0f, 0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glColor3f(1.0f, 1.0f, 1.0f);//White Color
	if (xAxisPlane >= 6.5f)
	{
		glColor3f(rColor2, gColor2, bColor2);
		rColor2 = rColor2 - 0.001f;
		gColor2 = gColor2 - 0.001f;
		bColor2 = bColor2 - 0.001f;

	}
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex2f(xAxisForColor, -0.1f);
	glVertex2f(0.0f, -0.1f);
	glEnd();
	xAxisForColor = xAxisForColor - 0.001f;


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xAxisPlane, 0.0f, 0.0f);
	gluLookAt(0, 0, 8, 0, 0, 0, 0, 1, 0);
	glColor3f(18.0f/255.0f, 136.0f/255.0f, 7.0f/255.0f);//Green Color
	if (xAxisPlane >= 6.5f)
	{
		glColor3f(rColor3, gColor3, bColor3);
			rColor3 = rColor3 - 0.001f;
			gColor3 = gColor3 - 0.001f;
			bColor3 = bColor3 - 0.001f;
	}
	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glVertex2f(xAxisForColor, -0.2f);
	glVertex2f(0.0f, -0.2f);
	glEnd();

	SwapBuffers(ghdc);
}

void ToggleFullScreen()
{
	MONITORINFO mi;
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
