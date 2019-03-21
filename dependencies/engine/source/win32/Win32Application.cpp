// WindowsProject2.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "GameLoop.h"
#include <memory>

#include <GL/glew.h>
#include <GL/wglew.h>

#define MAX_LOADSTRING				100
#define IDS_APP_TITLE				103
#define IDM_EXIT					105
#define IDI_WINDOWSPROJECT2			107
#define IDI_SMALL					108
#define IDC_WINDOWSPROJECT2			109

namespace
{
	std::unique_ptr<Engine::GameLoop> g_gameLoop;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
HDC hDC;			 // Private GDI Device Context

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void StartWin32Application()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance))
	{
		return;
	}
	g_gameLoop = std::make_unique<Engine::GameLoop>();
	int width, height;
	g_gameLoop->GetDefaultSize(width, height);
	g_gameLoop->OnWindowSizeChanged(width, height);

	MSG msg = {};
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			g_gameLoop->Tick();
			SwapBuffers(hDC);
		}
	}

	g_gameLoop.reset();
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT2));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT2);
	wcex.lpszClassName = L"GAME_ENGINE_SANDBOX";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance)
{
	hInst = hInstance; // Store instance handle in our global variable

	// Create window
	int w, h;
	g_gameLoop->GetDefaultSize(w, h);
	RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	HWND hWnd = CreateWindowEx(0, "GAME_ENGINE_SANDBOX", "Game Engine Sandbox", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, nullptr, nullptr, hInstance,
		nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(g_gameLoop.get()));

	static PIXELFORMATDESCRIPTOR pfd = // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1,							   // Version Number
		PFD_DRAW_TO_WINDOW |		   // Format Must Support Window
			PFD_SUPPORT_OPENGL |	   // Format Must Support OpenGL
			PFD_DOUBLEBUFFER,		   // Must Support Double Buffering
		PFD_TYPE_RGBA,				   // Request An RGBA Format
		(BYTE)16,					   // Select Our Color Depth
		0,
		0, 0, 0, 0, 0,  // Color Bits Ignored
		0,				// No Alpha Buffer
		0,				// Shift Bit Ignored
		0,				// No Accumulation Buffer
		0, 0, 0, 0,		// Accumulation Bits Ignored
		16,				// 16Bit Z-Buffer (Depth Buffer)
		8,				// No Stencil Buffer
		0,				// No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0,				// Reserved
		0, 0, 0			// Layer Masks Ignored
	};

	hDC = GetDC(hWnd);
	if (!hDC) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	//if (mMSAASupported) {
	//	pixelFormat = mMSAAPixelFormat;
	//}
	//else {
	//	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	//}

	//if (!pixelFormat) {
	//	KillGLWindow(fullscreen);
	//	MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
	//	return false;
	//}
	auto pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	auto hRC = wglCreateContext(hDC);
	if (!hRC) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		//KillGLWindow(fullscreen);
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);

	if (glewInit() != GLEW_OK) { // Enable GLEW
		MessageBox(NULL, "GLEW Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;
	}

	//GetClientRect(hWnd, &rc);
	//g_gameLoop->OnWindowSizeChanged(rc.right - rc.left, rc.bottom - rc.top);

	//g_gameLoop->Initialize(hWnd, rc.right - rc.left, rc.bottom - rc.top);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto game = reinterpret_cast<Engine::GameLoop*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
		if (game)
		{
			game->Tick();
		}
		else
		{
			PAINTSTRUCT ps;
			HDC hdc;
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
