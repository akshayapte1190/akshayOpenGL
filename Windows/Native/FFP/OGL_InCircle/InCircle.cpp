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

	TCHAR szAppName[] = TEXT("Double Buffer with Triangle");

	int initialize(void);
	void display(void);

	if (fopen_s(&gpFile, "InCircle.txt", "w") != 0)
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

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("OGL_InCircle"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);

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
	static GLfloat rotate = 0;

	GLfloat aside, bside, cside,semiperimeter, area, xside,yside, radius ;
	GLfloat 
		x1 = 0.0f, 
		y1 = 1.0f,
		x2=-1.0f,
		y2=-1.0f,
		x3=1.0f,
		y3=-1.0f;

	static GLfloat angle = 0.0f, xaxis = -2.0f, yaxis = -2.0f, circleYaxis = 2.0f,circleXaxis=2.0f, yAxisangle=0.0f, circleangle=0.0f, xAxis = 2.0f, yAxis = -2.0f,yAxisLine=2.0f;
	
	glClear(GL_COLOR_BUFFER_BIT);
	gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(xaxis, yaxis, -6.0f);

	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(x1, y1, 0.0f);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(x2, y2, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(x3, y3, 0.0f);
	if (xaxis <= 0.0f && yaxis <= 0.0f)
	{
		xaxis = (GLfloat)(xaxis + 0.0002);
		yaxis = (GLfloat)(yaxis + 0.0002);
	}
	angle = angle + 0.1f;
	glEnd();



	

	
	aside = sqrtf(((x2- x1)*(x2 - x1)) + ((y2-y1)*(y2 - y1)));

	bside = sqrtf(((x3-x2)*(x3 - x2))+((y3-y2) *(y3 - y2)));


	cside = sqrtf(((x3 - x1)*(x3-x1)) + ((y3 - y1)*(y3-y1)));

	semiperimeter =(GLfloat) (aside + bside + cside) / 2;

	area =sqrtf(semiperimeter*(semiperimeter - aside)*(semiperimeter - bside)*(semiperimeter-cside));
	radius = (GLfloat)(area / semiperimeter);

	xside =(GLfloat) (((x1*bside) + (x2*cside) + (x3*aside)) / (2*semiperimeter));
	yside = (GLfloat)(((y1*bside)+(y2*cside)+(y3*aside))/( 2*semiperimeter));




	if (xaxis >= 0)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(xAxis, yAxis, -6.0f);
		glRotatef(circleangle, 0.0f, 1.0f, 0.0f);
		glLineWidth(5.0f);
		glBegin(GL_POINTS);
		
		glColor3f(1.0f, 0.5f, 0.5f);

		for (GLfloat i = 0.0f; i < 2 * M_PI; i += 0.001f)
		{
			glVertex3f(xside + cosf(i)*radius, yside + sinf(i)*radius, 0.0f);
		}
		circleangle = circleangle + 0.1f;
		xAxis =(GLfloat) (xAxis - 0.0002);
		yAxis =(GLfloat) (yAxis + 0.0002);

		if (xAxis <= 0)
		{
			xAxis = 0.0f;
			yAxis = 0.0f;
		}
		glEnd();
		
		
		if (xAxis <= 0)
		{
			//circleYaxis = circleYaxis - 1.0f;
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			glTranslatef(0.0f, yAxisLine, -6.0f);
			glLineWidth(1.0f);
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2f(0.001f, 0.99f);
			glVertex2f(0.0011f, y3);


			if (yAxisLine <= 0)
				yAxisLine = 0.0f;

			yAxisLine = (GLfloat)(yAxisLine - 0.001);

			glEnd();
		}
	}
	///*	if (circleangle < 361)
			//circleangle = 0.0f;*/
	//}

	

	
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
		ShowCursor(true);
		gbFullScreen = false;
	}


}