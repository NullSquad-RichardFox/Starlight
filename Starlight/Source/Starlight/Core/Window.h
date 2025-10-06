#pragma once

#include "Base.h"
#include "Utility/Input.h"


struct GLFWwindow;

struct WindowProps
{
	uint32 Width = 960;
	uint32 Height = 540;
	std::string Title = "Starlight";
	void* Icon = nullptr;

	bool bWindowResizeEventActive = true;
	bool bWindowCloseEventActive = true;
	bool bKeyInputEventActive = true;
	bool bTextInputEventActive = true;
	bool bMouseScrollEventActive = false;
	bool bWindowInFocusEventActive = false;
	bool bRelativeMouseOffsetEventActive = true;
};

class Window
{
public:
	Window(const WindowProps& props);
	~Window();

	virtual void OnUpdate(float deltaTime);

	void FixAspectRatio(uint32 width, uint32 height);
	bool IsWindowClosed() const { return bShouldWindowClose; }

private:
	struct WindowData
	{
		std::function<void(uint32, uint32)> ResizeHandle;
		std::function<void()> CloseHandle;
		std::function<void(bool)> FocusHandle;
		std::function<void(char)> TextHandle;
		std::function<void(EKeyType, EInputAction, uint32)> InputHandle;
		std::function<void(float)> ScrollHandle;
		std::function<void(float, float)> MouseOffsetHandle;
	};

private:
	void OnWindowResizeEvent(uint32 width, uint32 height);
	void OnWindowCloseEvent();
	void OnWindowInFocusEvent(bool bGainedFocus);
	void OnTextInputEvent(char text);
	void OnInputEvent(EKeyType key, EInputAction inputAction, uint32 modKeys);
	void OnMouseScrollEvent(float offset);
	void OnMouseOffsetEvent(float xpos, float ypos);

	GLFWwindow* NativeWindow;
	WindowData Data;

	uint32 Width;
	uint32 Height;

	float MousePositionX;
	float MousePositionY;

	bool bShouldWindowClose;
};