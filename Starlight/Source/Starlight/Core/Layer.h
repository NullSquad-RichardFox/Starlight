#pragma once

#include "Starlight/Base.h"
#include "Starlight/Slate/SlateGeometry.h"


class Slate;
class Texture;

class Layer
{
public:
	Layer();
	
	virtual void OnUpdate(float deltaTime);
	
	// Saves the vertex data and textures, but also works with flush as the texture limit cannot be surpassed
	void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry);

	inline const std::shared_ptr<Slate>& GetRootSlate() const { return Root; }

private:
	std::shared_ptr<Slate> Root;
	
};

