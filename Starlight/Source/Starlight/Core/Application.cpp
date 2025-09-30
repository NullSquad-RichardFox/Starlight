#include "pcch.h"
#include "Application.h"
#include "Window.h"
#include "Utility/Time.h"
#include "Render/RenderUtilities.h"

#include "GLFW/glfw3.h"


Application::Application()
{
	MainWindow = nullptr;
}

void Application::Initialize()
{
	RAW_ASSERT(sAppInstance == nullptr, "Application class has already been created!");
	sAppInstance = this;

	RenderUtilities::Initialize();

	Time::Initialize();

	// Enables logging, creates log directory
	Logger::Initialize();

	WindowProps props;
	MainWindow = std::make_shared<Window>(props);
}

void Application::Shutdown()
{
	Logger::Shutdown();
	Time::Shutdown();
	RenderUtilities::Shutdown();

	sAppInstance = nullptr;
}

void Application::Run()
{
	while (true)
	{
		float deltaTime;
		Time::OnUpdate(deltaTime);

		MainWindow->OnUpdate(deltaTime);
	}
}
