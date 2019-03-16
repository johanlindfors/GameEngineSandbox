// WindowsProject2.cpp : Defines the entry point for the application.
//
#include <Windows.h>
#include "GameLoop.h"
#include <memory>

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

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

void StartWin32Application()
{
	g_gameLoop = std::make_unique<Engine::GameLoop>();

	HINSTANCE hInstance = GetModuleHandle(NULL);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance))
	{
		return;
	}

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

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);

	GetClientRect(hWnd, &rc);

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
