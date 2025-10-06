#pragma once

#include "Starlight/Base.h"


class Window;
class Layer;

class Application
{
public:
	Application();

	void Initialize();
	void Shutdown();
	
	void Run();
	void AddLayer(const std::shared_ptr<Layer>& layer);

private:
	inline static Application* sAppInstance = nullptr;

	std::shared_ptr<Window> MainWindow;
	std::vector<std::shared_ptr<Layer>> Layers;
};