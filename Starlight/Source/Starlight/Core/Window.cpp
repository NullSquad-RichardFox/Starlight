#include "Window.h"
#include "Starlight/Render/RenderUtilities.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


Window::Window(const WindowProps& props)
{
	bShouldWindowClose = false;

	// Creates GLFW window
	Width = props.Width;
	Height = props.Height;
	NativeWindow = glfwCreateWindow(Width, Height, props.Title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(NativeWindow);

	// Loads GLAD
	int32 status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(status, "Glad initialization failed");

	// Sets up GLAD
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glDepthFunc(GL_LESS);

	Data.CloseHandle = std::bind(&Window::OnWindowCloseEvent, this);
	Data.FocusHandle = std::bind(&Window::OnWindowInFocusEvent, this, std::placeholders::_1);
	Data.InputHandle = std::bind(&Window::OnInputEvent, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	Data.MouseOffsetHandle = std::bind(&Window::OnMouseOffsetEvent, this, std::placeholders::_1, std::placeholders::_2);
	Data.ResizeHandle = std::bind(&Window::OnWindowResizeEvent, this, std::placeholders::_1, std::placeholders::_2);
	Data.ScrollHandle = std::bind(&Window::OnMouseScrollEvent, this, std::placeholders::_1);
	Data.TextHandle = std::bind(&Window::OnTextInputEvent, this, std::placeholders::_1);

	// Sets event-relative data
	glfwSetWindowUserPointer(NativeWindow, &Data);

	// Window events
	if (props.bWindowCloseEventActive)
	{
		LOG("Window {} event WindowCloseEvent set!", (void*)NativeWindow);
		glfwSetWindowCloseCallback(NativeWindow, [](GLFWwindow* window) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->CloseHandle();
		});
	}

	if (props.bWindowInFocusEventActive)
	{
		LOG("Window {} event WindowInFocusEvent set!", (void*)NativeWindow);
		glfwSetWindowFocusCallback(NativeWindow, [](GLFWwindow* window, int32 focus) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->FocusHandle(focus == 1);
		});
	}

	if (props.bWindowResizeEventActive)
	{
		LOG("Window {} event WindowResizeEvent set!", (void*)NativeWindow);
		glfwSetWindowSizeCallback(NativeWindow, [](GLFWwindow* window, int32 width, int32 height) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->ResizeHandle((uint32)width, (uint32)height);
		});
	}

	if (props.bKeyInputEventActive)
	{
		LOG("Window {} event KeyCallbackEvent and MouseButtonCallback set!", (void*)NativeWindow);
		glfwSetKeyCallback(NativeWindow, [](GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			EInputAction inputAction;
			switch (action)
			{
			case GLFW_PRESS:
				inputAction = EInputAction::Triggered;
				break;

			case GLFW_RELEASE:
				inputAction = EInputAction::Released;
				break;

			case GLFW_REPEAT:
				inputAction = EInputAction::Pressed;
				break;
			}

			data->InputHandle(EKeyType(key), inputAction, (uint32)mods);
		});

		glfwSetMouseButtonCallback(NativeWindow, [](GLFWwindow* window, int32 button, int32 action, int32 mods) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			EInputAction inputAction;
			switch (action)
			{
			case GLFW_PRESS:
				inputAction = EInputAction::Triggered;
				break;

			case GLFW_RELEASE:
				inputAction = EInputAction::Released;
				break;

			case GLFW_REPEAT:
				inputAction = EInputAction::Pressed;
				break;
			}

			data->InputHandle(EKeyType(button+400), inputAction, (uint32)mods);
		});
	}

	if (props.bTextInputEventActive)
	{
		LOG("Window {} event CharCallbackEvent set!", (void*)NativeWindow);
		glfwSetCharCallback(NativeWindow, [](GLFWwindow* window, uint32 codepoint) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->TextHandle((char)codepoint);
		});
	}

	if (props.bRelativeMouseOffsetEventActive)
	{
		LOG("Window {} event RelativeMouseOffsetEvent set!", (void*)NativeWindow);
		glfwSetCursorPosCallback(NativeWindow, [](GLFWwindow* window, double xpos, double ypos) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->MouseOffsetHandle((float)xpos, (float)ypos);
		});
	}

	if (props.bMouseScrollEventActive)
	{
		LOG("Window {} event MouseScrollEvent set!", (void*)NativeWindow);
		glfwSetScrollCallback(NativeWindow, [](GLFWwindow* window, double xoffset, double yoffset) {
			WindowData* data = (WindowData*)glfwGetWindowUserPointer(window);

			data->ScrollHandle((float)yoffset);
		});
	}
}

Window::~Window()
{
	glfwDestroyWindow(NativeWindow);
	NativeWindow = nullptr;
}

void Window::OnUpdate(float deltaTime)
{
	glfwPollEvents();
	glfwSwapBuffers(NativeWindow);

	RenderUtilities::Clear();
	RenderUtilities::SetClearColor(glm::vec4(0.1f));
}

void Window::FixAspectRatio(uint32 width, uint32 height)
{
	glfwSetWindowAspectRatio(NativeWindow, width, height);
}

void Window::OnWindowResizeEvent(uint32 width, uint32 height)
{
	Width = width;
	Height = height;

	RenderUtilities::SetViewport(Width, Height);
}

void Window::OnWindowCloseEvent()
{
	bShouldWindowClose = true;
}

void Window::OnWindowInFocusEvent(bool bGainedFocus)
{

}

void Window::OnTextInputEvent(char text)
{
}

void Window::OnInputEvent(EKeyType key, EInputAction inputAction, uint32 modKeys)
{
	InputSubsystem::ProcessKey(key, inputAction, modKeys);
}

void Window::OnMouseScrollEvent(float offset)
{
	// TODO: add mouse scroll input 
}

void Window::OnMouseOffsetEvent(float xpos, float ypos)
{
	xpos = xpos / (float)Width * 1920.f;
	ypos = ypos / (float)Height * 1080.f;
	ypos = 1080.f - ypos;

	InputSubsystem::ProcessMouse(xpos - MousePositionX, ypos - MousePositionY);
	MousePositionX = xpos;
	MousePositionY = ypos;
}
