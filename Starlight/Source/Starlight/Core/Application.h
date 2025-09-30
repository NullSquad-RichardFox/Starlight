#pragma once


class Window;

class Application
{
public:
	Application();

	void Initialize();
	void Shutdown();
	
	void Run();

private:
	inline static Application* sAppInstance = nullptr;

	std::shared_ptr<Window> MainWindow;
};