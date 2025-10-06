#include "Layer.h"
#include "Starlight/Slate/Overlay.h"


Layer::Layer()
{
	Root = std::make_shared<Overlay>();
}

void Layer::Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry)
{
	Root->Draw(boxGeometry, textGeometry);
}