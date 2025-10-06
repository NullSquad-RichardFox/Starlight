#include "Overlay.h"
#include "Slate.h"


Overlay* Overlay::AddChild(Slate* slate)
{
	auto s = std::make_shared<Slate>();
	s.reset(slate);
	Children.push_back(s);
	return this;
}

void Overlay::Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry)
{
	for (const auto& slate : Children)
	{
		slate->Draw(boxGeometry, textGeometry);
	}
}
