#include "Starlight/Starlight.h"


int main()
{
	Application app;
	app.Initialize();

	auto l = std::make_shared<Layer>();
	l->GetRootSlate()
		->AddChild(
			NewSlate<Slate>()
			->SetPosition(glm::vec2(0.0))
			->SetSize(glm::vec2(100))
			->SetColor(glm::vec4(1, 0, 0, 1))
			->SetZOrder(0)
			->SetIsStatic(true))
		->AddChild(
			NewSlate<Slate>()
			->SetPosition(glm::vec2(400))
			->SetSize(glm::vec2(50))
			->SetColor(glm::vec4(0, 1, 0, 1)));

	app.AddLayer(l);

	app.Run();
	app.Shutdown();
}