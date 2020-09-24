#pragma once

//win32api
#include <Windows.h>

class Window
{
public:

	Window();

	bool init();
	bool broadcast();
	bool release();
	bool isRun();

	// events
	virtual void onCreate() = 0;
	virtual void onUpdate() = 0;
	virtual void onDestroy();

	~Window();

protected:
	HWND m_hwnd;
	bool m_is_run;
};