#pragma once


struct GLFWwindow;

struct WindowProps
{
	uint32 Width = 600;
	uint32 Height = 800;
	std::string Title = "Starlight";
	void* Icon = nullptr;

	bool bWindowResizeEventActive = true;
	bool bWindowCloseEventActive = true;
	bool bKeyInputEventActive = false;
	bool bTextInputEventActive = false;
	bool bMouseScrollEventActive = false;
	bool bWindowInFocusEventActive = false;
	bool bRelativeMouseOffsetEventActive = false;
};

class Window
{
public:
	Window(const WindowProps& props);
	~Window();

	virtual void OnUpdate(float deltaTime);

private:
	struct WindowData
	{
		int32 Width, Height;
		std::string Title;

		double CursorPosX, CursorPosY;
	};

private:
	void OnWindowResizeEvent(uint32 width, uint32 height);
	void OnWindowCloseEvent();
	void OnWindowInFocusEvent();
	void OnTextInputEvent();
	void OnKeyInputEvent();
	void OnMouseInputEvent();
	void OnMouseScrollEvent();
	void OnMouseOffsetEvent();

	GLFWwindow* NativeWindow;
	WindowData Data;
};