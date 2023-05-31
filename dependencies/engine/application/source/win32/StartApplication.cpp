#include "game-loop/GameLoop.hpp"
#include <Windows.h>
#include <windowsx.h>
#include <memory>
#include "glwrapper.hpp"
#include "input/IInputManager.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Config.hpp"
#include "utilities/StringHelpers.hpp"
#include "OutputDebug.hpp"

using namespace Engine;
using namespace Utilities;

namespace {
	std::unique_ptr<GameLoop> g_gameLoop;
};

// Global Variables:
HINSTANCE hInst; // current instance
HDC hDC;         // Private GDI Device Context

// Forward declarations of functions included in this code module:
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void startApplication() {
	const HINSTANCE hInstance = GetModuleHandle(nullptr);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	g_gameLoop = std::make_unique<GameLoop>();
	if (!InitInstance(hInstance)) {
		return;
	}
	const auto config = IOCContainer::instance().resolve<Config>();
	g_gameLoop->initialize(config);
	int width, height;
	width = config->width;
	height = config->height;
	if (width == 0 || height == 0) {
		g_gameLoop->getDefaultSize(width, height);
	}
	g_gameLoop->updateWindowSize(width, height);

	MSG msg = {};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			g_gameLoop->tick();
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
	wcex.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wcex.hCursor = nullptr;
	wcex.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = L"GAME_ENGINE_SANDBOX";
	wcex.hIconSm = nullptr;

	return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance) {
	hInst = hInstance; // Store instance handle in our global variable

	const auto config = IOCContainer::instance().resolve<Config>();
	int width, height;
	width = config->width;
	height = config->height;
	if (width == 0 || height == 0) {
		g_gameLoop->getDefaultSize(width, height);
	}
	RECT rc = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
	
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	const HWND hWnd = CreateWindowEx(
		0, "GAME_ENGINE_SANDBOX", config->title.c_str(),
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
		static_cast<BYTE>(16),         // Select Our Color Depth
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

	const auto pixelFormat = ChoosePixelFormat(hDC, &pfd);
	if (!SetPixelFormat(hDC, pixelFormat, &pfd)) {
		return false;
	}

	const auto hRC = wglCreateContext(hDC);
	if (!hRC) {
		return false;
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		return false;
	}

	Info("GL_VERSION  : %s", glGetString(GL_VERSION));
	Info("GL_RENDERER : %s", glGetString(GL_RENDERER));
	Info("GL_SHADING_LANGUAGE_VERSION : %s", glGetString(GL_SHADING_LANGUAGE_VERSION));

	ShowWindow(hWnd, 5);
	UpdateWindow(hWnd);
	if (glewInit() != GLEW_OK) { // Enable GLEW
		return false;
	}

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) 
{
	const auto gameParam = GetWindowLongPtr(hWnd, GWLP_USERDATA);
	auto game = reinterpret_cast<Engine::GameLoop *>(gameParam);
	std::shared_ptr<IInputManager> input;
	if(game){
		input = game->getInput();
	}

	switch (message) {
	case WM_SIZE:
		if (game) {
			game->updateWindowSize(LOWORD(lParam), HIWORD(lParam));
			g_gameLoop->tick();
			SwapBuffers(hDC);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		if(input){
			input->addKeyboardEvent(static_cast<unsigned int>(wParam), true);
		}
		break;
	case WM_KEYUP:
		if(wParam == VK_ESCAPE) {
			PostQuitMessage(0);
			break;
		}
		if(input){
			input->addKeyboardEvent(static_cast<unsigned int>(wParam), false);
		}
		break;
	case WM_LBUTTONDOWN:
		if (input) {
			auto xpos = GET_X_LPARAM(lParam);
			auto ypos = GET_Y_LPARAM(lParam);
			input->addMouseEvent(MouseButton::Left, MouseButtonState::Pressed , xpos, ypos);
		}
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
