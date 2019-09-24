#pragma once 
#include "GlobalConstants.h"
#include "Platform.h"
#include "Clock.h"

#include <Windows.h>
#include <glew.h>
#include <gl/GL.h>

class Win32Clock : public Clock {
private:
	LARGE_INTEGER thisFrame, lastFrame, frequency, delta;
public:
	Win32Clock() : thisFrame({ 0 }), lastFrame({ 0 }), frequency({ 0 }), delta({ 0 }) { deltaTime = 0.f; }

	void Initialize() override {
		if (!QueryPerformanceFrequency(&frequency)) { return; }
		if (!QueryPerformanceCounter(&lastFrame)) { return; }
	}

	void StartFrame() override {
		if (!QueryPerformanceCounter(&thisFrame)) { return; }
		delta.QuadPart = thisFrame.QuadPart - lastFrame.QuadPart;
		deltaTime = (float)delta.QuadPart / (float)frequency.QuadPart;
	}

	void EndFrame() override {
		lastFrame.QuadPart = thisFrame.QuadPart;
	}
};

LRESULT CALLBACK WindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam);


class Win32Platform: public Platform {
private:
	HDC deviceContext;
	HGLRC openGLContext;
	HWND window;

	void InitializePixelStuff() override {
		PIXELFORMATDESCRIPTOR pixelDescriptor = { 0 };
		pixelDescriptor.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelDescriptor.nVersion = 1;
		pixelDescriptor.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		pixelDescriptor.iPixelType = PFD_TYPE_RGBA;
		pixelDescriptor.cColorBits = 32;

		int pixelFormatter = ChoosePixelFormat(deviceContext, &pixelDescriptor);

		if (!pixelFormatter) { ERROR_BOX("Could not choose a pixel format"); return; }
		if (!SetPixelFormat(deviceContext, pixelFormatter, &pixelDescriptor)) { ERROR_BOX("Could not set pixel format."); return; }

		DescribePixelFormat(deviceContext, pixelFormatter, sizeof(PIXELFORMATDESCRIPTOR), &pixelDescriptor);
	}

public:
	Win32Clock clock;
	Win32Platform() : Platform(&clock) { deviceContext = 0, openGLContext = 0; quit = false; }

	void CreateWin32Window(HINSTANCE instance) {
		WNDCLASSA windowClass = { 0 };
		windowClass.style = CS_HREDRAW | CS_VREDRAW;
		windowClass.hInstance = instance;
		windowClass.lpfnWndProc = WindowProc;
		windowClass.lpszClassName = WINDOW_TITLE;

		if (!RegisterClassA(&windowClass)) { ERROR_BOX("Failed to register Win32Window class!"); return; }

		window = CreateWindowA(windowClass.lpszClassName, WINDOW_TITLE, WS_VISIBLE | WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH_SMALL, WINDOW_HEIGHT_SMALL, 0, 0, instance, 0);
		if (!window) { ERROR_BOX("Failed to create Win32Window."); return; }

		deviceContext = GetDC(window);

		InitializePixelStuff();

		openGLContext = wglCreateContext(deviceContext);
		wglMakeCurrent(deviceContext, openGLContext);
	}

	void HandleMessages() {
		MSG message = { 0 };

		while (PeekMessageA(&message, 0, 0, 0, PM_REMOVE)) {
			if (message.message == WM_QUIT)
				quit = false;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}

	void SwapWindowBuffers() {
		SwapBuffers(deviceContext);
	}

	~Win32Platform() {
		wglMakeCurrent(0, 0);
		wglDeleteContext(openGLContext);
		ReleaseDC(window, deviceContext);
	}
};