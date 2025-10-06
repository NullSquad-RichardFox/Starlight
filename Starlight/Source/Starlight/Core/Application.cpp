#include "Application.h"
#include "Window.h"
#include "Utility/Time.h"
#include "Utility/Input.h"
#include "Render/RenderUtilities.h"
#include "Render/Renderer.h"

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
	InputSubsystem::Initialize();

	// Enables logging, creates log directory
	Logger::Initialize();

	WindowProps props;
	MainWindow = std::make_shared<Window>(props);
	MainWindow->FixAspectRatio(16, 9);

	Renderer::Intialize();
}

void Application::Shutdown()
{
	Renderer::Shutdown();
	Logger::Shutdown();
	InputSubsystem::Shutdown();
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

		if (MainWindow->IsWindowClosed())
		{
			MainWindow.reset();
			return;
		}

		Renderer::OnUpdate(deltaTime);

		for (const auto& layer : Layers)
			Renderer::RenderLayer(layer);
	}
}

void Application::AddLayer(const std::shared_ptr<Layer>& layer)
{
	Layers.push_back(layer);
}
