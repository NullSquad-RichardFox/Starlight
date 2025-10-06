#pragma once

#include "Base.h"
#include "Slate/SlateGeometry.h"


class Overlay;
class Texture;

class Layer
{
public:
	Layer();
	inline const std::shared_ptr<Overlay>& GetRootSlate() const { return Root; }

	// Saves the vertex data and textures, but also works with flush as the texture limit cannot be surpassed
	void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry);

private:
	std::shared_ptr<Overlay> Root;
	
};

