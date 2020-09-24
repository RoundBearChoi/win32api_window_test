#include "Window.h"

Window* window = nullptr;

Window::Window()
{
	// must initialize 
	m_hwnd = 0;
	m_is_run = false;
}

#define MAX_CLASS_NAME_LENGTH 256
WCHAR ClassName[MAX_CLASS_NAME_LENGTH];
WCHAR WindowName[MAX_CLASS_NAME_LENGTH];

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{

	case WM_CREATE:
	{
		window->onCreate();
		break;
	}

	case WM_DESTROY:
	{
		window->onDestroy();
		PostQuitMessage(0);
		break;
	}

	default:
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}

bool Window::init()
{
	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDI_APPLICATION);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.style = NULL;

	// important (handle events)
	wc.lpfnWndProc = WndProc;

	// could be string depending on version
	wcscpy_s(ClassName, TEXT("My Window Class"));
	wc.lpszClassName = ClassName;

	// could be string depending on version
	wc.lpszMenuName = nullptr;

	if (!RegisterClassEx(&wc))
	{
		return false;
	}

	if (!window)
	{
		window = this;
	}

	wcscpy_s(WindowName, TEXT("Untitled Window"));

	m_hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW,
		ClassName,
		WindowName,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		1024,
		768,
		NULL,
		NULL,
		NULL,
		NULL);

	if (!m_hwnd)
	{
		return false;
	}

	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	// indicate window is initialized
	m_is_run = true;

	return true;
}

bool Window::broadcast()
{
	MSG msg;

	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->onUpdate();

	// relax cpu
	Sleep(0);

	return true;
}

bool Window::release()
{
	if (!DestroyWindow(m_hwnd))
	{
		return false;
	}

	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

void Window::onDestroy()
{
	m_is_run = false;
}

Window::~Window()
{

}