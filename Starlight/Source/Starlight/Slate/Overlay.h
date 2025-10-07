#pragma once

#include "Starlight/Base.h"
#include "SlateGeometry.h"


class Slate;

class Overlay
{
public:
	Overlay* AddChild(Slate* slate);

	virtual void OnUpdate(float deltaTime);
	void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry);

private:
	std::vector<std::shared_ptr<Slate>> Children;
};