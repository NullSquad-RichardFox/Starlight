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
};