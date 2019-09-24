#include <iostream>
#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>

#define ERROR_BOX(message) (MessageBoxA(0, message, "ERROR", MB_OK))
#define VICTORY_BOX(message) (MessageBoxA(0, message, "VICTORY", MB_OK))

#include "App.h"
#include "Platform.h"
#include "Win32Platform.h"

static Win32Platform platform = Win32Platform();
static App app = App(&platform);

LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam) {

	LRESULT result = 0;

	if (msg == WM_KEYDOWN || msg == WM_KEYUP) {
		bool keyIsDown = msg == WM_KEYDOWN;
		int keyIndex = 0;

		if (wParam >= 'A' && wParam <= 'Z')
			keyIndex = KEY_A + (wParam - 'A');

		if (wParam == VK_ESCAPE)
			app.quit = true;

		platform.keypad[keyIndex] = keyIsDown;
	}

	switch (msg) {
	case WM_CLOSE: {
		app.quit = true;
	} break;

	case WM_SIZE: {
		glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
		RECT windowRect = { 0 };
		GetWindowRect(window, &windowRect);
		platform.SetWindowWidthAndHeight(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	} break;

	case WM_PAINT: {
		PAINTSTRUCT paint;
		BeginPaint(window, &paint);
		EndPaint(window, &paint);
	} break;

	default: {
		result = DefWindowProc(window, msg, wParam, lParam);
	} break;
	}

	return result;
}

int CALLBACK WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR cmd, int code) {
	platform.CreateWin32Window(instance);
	platform.clock.Initialize();

	app.Initialize();

	while (!app.quit) {
		platform.clock.StartFrame();
		platform.HandleMessages();

		app.Update();

		platform.SwapWindowBuffers();
		platform.clock.EndFrame();
	}
}