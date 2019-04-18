#include "GameLoop.h"
#include <Windows.h>
#include <memory>
#include "glwrapper.h"
#include "input/IInputManager.h"

namespace {
	std::unique_ptr<Engine::GameLoop> g_gameLoop;
};

// Global Variables:
HINSTANCE hInst; // current instance
HDC hDC;         // Private GDI Device Context

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void StartWin32Application() {
	HINSTANCE hInstance = GetModuleHandle(NULL);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	g_gameLoop = std::make_unique<Engine::GameLoop>();
	if (!InitInstance(hInstance)) {
		return;
	}
	g_gameLoop->Initialize();
	int width, height;
	g_gameLoop->GetDefaultSize(width, height);
	g_gameLoop->UpdateWindowSize(width, height);

	MSG msg = {};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			g_gameLoop->Tick();
			SwapBuffers(hDC);
		}
	}

	g_gameLoop.reset();
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = nullptr;
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"GAME_ENGINE_SANDBOX";
	wcex.hIconSm = nullptr;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance) {
	hInst = hInstance; // Store instance handle in our global variable

	// Create window
	int w, h;
	g_gameLoop->GetDefaultSize(w, h);
	RECT rc = { 0, 0, static_cast<LONG>(w), static_cast<LONG>(h) };

	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindowEx(
		0, "GAME_ENGINE_SANDBOX", "Game Engine Sandbox",
		WS_OVERLAPPEDWINDOW, 0, 0,
		rc.right - rc.left, rc.bottom - rc.top, 
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) {
		return FALSE;
	}

	auto gameLoop = g_gameLoop.get();
	SetWindowLongPtr(hWnd, GWLP_USERDATA,
		reinterpret_cast<LONG_PTR>(gameLoop));

	static PIXELFORMATDESCRIPTOR
		pfd = // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1,                             // Version Number
		PFD_DRAW_TO_WINDOW |           // Format Must Support Window
		PFD_SUPPORT_OPENGL |		   // Format Must Support OpenGL
		PFD_DOUBLEBUFFER,              // Must Support Double Buffering
		PFD_TYPE_RGBA,                 // Request An RGBA Format
		(BYTE)16,                      // Select Our Color Depth
		0,
		0,
		0,
		0,
		0,
		0, // Color Bits Ignored
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0,
		0,
		0,
		0,              // Accumulation Bits Ignored
		16,             // 16Bit Z-Buffer (Depth Buffer)
		8,              // No Stencil Buffer
		0,              // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0,              // Reserved
		0,
		0,
		0 // Layer Masks Ignored
	};

	hDC = GetDC(hWnd);
	if (!hDC) {
		return false;
	}

	auto pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
		return false;
	}

	auto hRC = wglCreateContext(hDC);
	if (!hRC) {
		return false;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		return false;
	}

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);

	if (glewInit() != GLEW_OK) { // Enable GLEW
		return false;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	auto gameParam = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	auto game = reinterpret_cast<Engine::GameLoop *>(gameParam);
	std::shared_ptr<IInputManager> input;
	if(game){
		input = game->GetInput();
	}

	switch (message) {
	case WM_SIZE:
		if (game) {
			game->UpdateWindowSize(LOWORD(lParam), HIWORD(lParam));
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(input){
			input->AddKeyboardEvent(static_cast<unsigned int>(wParam), true);
		}
		break;
	case WM_KEYUP:
		if(input){
			input->AddKeyboardEvent(static_cast<unsigned int>(wParam), false);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
