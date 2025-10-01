#pragma once

#include "Base.h"
#include "SlateGeometry.h"


class Texture;

class Slate
{
public:
	Slate();

	Slate* AddChild(Slate* slate);
	Slate* SetPosition(glm::vec2 position);
	Slate* SetSize(glm::vec2 size);
	Slate* SetColor(glm::vec4 color);
	Slate* SetTexture(const std::shared_ptr<Texture>& texture);
	Slate* SetZOrder(float zOrder);
	Slate* SetIsStatic(bool bIsStatic);

	void Draw(SlateGeometry& boxGeometry, SlateGeometry textGeometry);

private:
	std::vector<std::shared_ptr<Slate>> Children;

	glm::vec2 Position;
	glm::vec2 Size;
	glm::vec4 Color;
	std::shared_ptr<Texture> SlateTexture;
	float ZOrder;

	uint32 DataOffset;
	uint32 DataSize;
	bool bStatic;
	uint32 SlateID;
};

template<typename T>
static T* NewSlate() 
{ 
	static_assert(std::is_base_of_v<Slate, T>);
	
	return new T();
}