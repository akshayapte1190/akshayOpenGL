#include<Windows.h>
#include<stdio.h>
#include<GL/GL.h>

#pragma comment(lib,"opengl32.lib")
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

//global varibale declaration
HDC ghdc = NULL;
HGLRC ghrc = NULL;
HWND ghwnd = NULL;
bool gbActiveWindow = false;
FILE *gpFile = NULL;
bool gbFullScreen = false;
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

//WndProc Prototype
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//variable declaration
	WNDCLASSEX wndclass;
	MSG msg;
	HWND hwnd;
	TCHAR szAppName[] = TEXT("Native Full Screen App");
	int iRet = 0;
	bool bDone = false;

	//Function Declarations
	int initialize(void);

	//code
	//File Open For Dubugging
	if (fopen_s(&gpFile, "Log.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Log File can not be created\n"), TEXT("Error"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpFile, "Log file is successfully created\n");
	}

	//wndclass initialization
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW|CS_OWNDC;
	wndclass.cbWndExtra = 0;
	wndclass.cbClsExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);


	//Register Class
	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(WS_EX_APPWINDOW, szAppName, TEXT("OGL_Native_Window"), WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE, 100, 100, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, hInstance, NULL);


	//Error Checking
	if (hwnd == NULL)
	{
		MessageBox(NULL, TEXT("Window not created"), TEXT("Error"), MB_OK);
		exit(0);
	}

	//assign Hangle to Global Handle
	ghwnd = hwnd;

	//Get return value from initialization
	iRet = initialize();

	//code to check the value of iRet
	if (iRet == -1)
	{
		fprintf(gpFile, "Choose Pixel Format Failed.....");
		DestroyWindow(hwnd);
	}//end of 1 iret value if block

	else if (iRet == -2)
	{
		fprintf(gpFile, "Set Pixel Format index Failed.....");
		DestroyWindow(hwnd);
	}

	else if (iRet == -3)
	{
		fprintf(gpFile, "wglCurrentContext failed....");
		DestroyWindow(hwnd);
	}

	else if (iRet == -4)
	{
		fprintf(gpFile, "wglMakeCurrent Failed....");
		DestroyWindow(hwnd);
	}

	else
	{
		fprintf(gpFile, "initialized successful.......");
	}

	//Window Created in memory to display it on screen se below function
	ShowWindow(hwnd, nCmdShow);

	//Keep window foreground
	SetForegroundWindow(hwnd);

	//Keep focus on window
	SetFocus(hwnd);

	//Game Loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			//Check if message is WM_QUIT
			if (msg.message == WM_QUIT)
			{
				bDone = true;
			}//End of msg.message if block
			else
			{
				//if message is not WM_QUIT
				//Keep loop as GetMessage loop
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}//end of else block

		}//End If outer PeekMessage block
		else
		{
			if (gbActiveWindow == true)
			{
				//Here Call Update
			}//End Of if gbActive block

		}//End of else block

	}//End While

	//return if message is WM_QUIT and end program
	return((int)msg.wParam);

}//End Of WinMain


 //WndProc Definition
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function declaration
	void ToggleFullScreen(void);
	void resize(int, int);
	void display(void);
	void uninitialize(void);

	//switch for Messsages
	switch (iMsg)
	{
	case WM_SETFOCUS:
		//if focus is on Window then game should play
		gbActiveWindow = true;
		break;

	case WM_KILLFOCUS:
		//if focus is not on current window then game/animation should pause
		gbActiveWindow = false;
		break;

	case WM_SIZE:
		//whenever we resize window at that time it call to resize function
		resize(LOWORD(lParam),HIWORD(lParam));
		break;

	case WM_PAINT:
		//display this should be done in single buffering
		display();
		break;

	case WM_CLOSE:
		//Close the window
		DestroyWindow(hwnd);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//on escape Window gets closed
			DestroyWindow(hwnd);
			break;
		case 0x46:
			//on 'F' or 'f' Window gets full screen
			ToggleFullScreen();
			break;
		}//End of Switch of wParam under WM_KEYDOWN
		break;

	case WM_DESTROY:
		uninitialize();
		//When we pass 0 it goes to message loop internally calls WM_QUIT and exit the program
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

int initialize(void)
{
	//Function Declaration
	void resize(int, int);

	//variable Declaration
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelFormatIndex;


	//code
	//initialize pfd structure
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	pfd.iPixelType = PFD_TYPE_RGBA;

	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;


	//Get Plain Device Context from OS
	ghdc = GetDC(ghwnd);

	//if ChoosePixelFormat function gets fail the value is zero otherwise it always should be 1
	//Match Pixel Format in OS and gets it's index
	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelFormatIndex == 0)
	{
		return -1;
	}//end of iPixelFormatIndex if block

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == FALSE)
	{
		return -2;
	}//End of SetPixelFormat if block

	//do ghrc as specalist
	ghrc = wglCreateContext(ghdc);

	if (ghrc == NULL)
	{
		return -3;
	}//end of ghrc if block

	//Make current painter  to ghrc
	if (wglMakeCurrent(ghdc, ghrc) == NULL)
	{
		//if not return error
		return -4;
	}

	//Clear the screen by OpenGL Color
	//this function checks that OpenGL is enable or not
	//When redendering gets started at that time it starts to render screen as blue
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);


	//Warm up cll to resize it is convention
	resize(WIN_WIDTH, WIN_HEIGHT);


	return (0);
}//End of initialize function

void uninitialize(void)
{
	//Check wether full screen or not & if it is then restore to normal size
	//and then procees for uninitialize

	if (gbFullScreen == true)
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,HWND_TOP,0,0,0,0,SWP_NOZORDER|SWP_NOMOVE|SWP_NOSIZE|SWP_NOOWNERZORDER);
		ShowCursor(true);
		
	}//end of gbFullScreen if block

	//if current Device contect is ghrc then make it NULL
	if (wglGetCurrentContext() == ghrc)
	{
		//Make ghrc and ghdc as NULL
		wglMakeCurrent(NULL, NULL);

	}//End of wglCurrentContext if block

	//if ghrc is not NULL
	if (ghrc)
	{
		//Delete the ghrc context
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}//end of ghrc NULL block

	//Check if normal Context is there if yes,Release it
	if (ghdc)
	{
		ReleaseDC(ghwnd,ghdc);
		ghdc = NULL;

	}//End of ghdc if block

	//check whether file is Open if yes then close the file
	if (gpFile)
	{
		fprintf(gpFile, "File is closed\n");
		fclose(gpFile);
		gpFile = NULL;
	}//end of if block gpFile

}//End of uninitialize function


//resize function definition
void resize(int width, int height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}//End of resize function

//display function definition
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}//End of disply function


//Starting of ToggleFullScreen Function
void ToggleFullScreen(void)
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
				SetWindowPos(ghwnd,
					HWND_TOP,
					mi.rcMonitor.left,
					mi.rcMonitor.top,
					mi.rcMonitor.right -
					mi.rcMonitor.left,
					mi.rcMonitor.bottom -
					mi.rcMonitor.top,
					SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
		gbFullScreen = true;
	}
	else
	{


		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);

		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd,
			HWND_TOP,
			0, 0, 0, 0, SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER);
		ShowCursor(true);
		gbFullScreen = false;
	}
}//End of ToggleFullScreen function

