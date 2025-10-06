#include "Starlight/Starlight.h"
#include "Starlight/Slate/TextSlate.h"
#include "Starlight/Slate/Overlay.h"
#include "Starlight/Slate/ButtonSlate.h"


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
			NewSlate<TextSlate>()
			->SetText("Hello")
			->SetPosition(glm::vec2(400)))
		->AddChild(
			NewSlate<ButtonSlate>()
			->SetPosition(500, 500)
			->SetSize(100, 40));

	app.AddLayer(l);

	app.Run();
	app.Shutdown();
}