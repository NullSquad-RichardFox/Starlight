#include "Layer.h"
#include "Slate/Slate.h"


Layer::Layer()
{
	Root = std::make_shared<Slate>();
}

void Layer::Draw(SlateGeometry& boxGeometry, SlateGeometry textGeometry)
{
	Root->Draw(boxGeometry, textGeometry);
}