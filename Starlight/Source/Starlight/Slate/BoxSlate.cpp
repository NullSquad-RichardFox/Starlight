#include "BoxSlate.h"
#include "Starlight/Render/Texture.h"


BoxSlate::BoxSlate()
{
	bStatic = false;
	SlateTexture = nullptr;
	Color = glm::vec4(1.0f);
}

BoxSlate* BoxSlate::SetPosition(glm::vec2 position)
{
	Position = position;
	return this;
}

BoxSlate* BoxSlate::SetPosition(float x, float y)
{
	Position = glm::vec2(x, y);
	return this;
}

BoxSlate* BoxSlate::SetSize(glm::vec2 size)
{
	Size = size;
	return this;
}

BoxSlate* BoxSlate::SetSize(float x, float y)
{
	Size = glm::vec2(x, y);
	return this;
}

BoxSlate* BoxSlate::SetColor(glm::vec4 color)
{
	Color = color;
	return this;
}

BoxSlate* BoxSlate::SetColor(float r, float g, float b, float a)
{
	Color = glm::vec4(r, g, b, a);
	return this;
}

BoxSlate* BoxSlate::SetTexture(const std::shared_ptr<Texture>& texture)
{
	SlateTexture = texture;
	return this;
}

BoxSlate* BoxSlate::SetTexture(const std::string& textureSrc)
{
	SlateTexture = std::make_shared<Texture>(textureSrc);
	return this;
}

BoxSlate* BoxSlate::SetZOrder(float zOrder)
{
	ZOrder = zOrder;
	return this;
}

void BoxSlate::Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry)
{
	Slate::Draw(boxGeometry, textGeometry);

	std::vector<float> boxVertexData;
	glm::vec2 position;
	position.x = Position.x / 540.0f - 1.7777777f;
	position.y = Position.y / 540.0f - 1;
	glm::vec2 size = Size / 540.0f;
	float zOrder = -1 / (ZOrder + 1) + 1;

	// Bottom left
	boxVertexData.push_back(position.x);
	boxVertexData.push_back(position.y);
	boxVertexData.push_back(zOrder);
	boxVertexData.push_back(0.0f);
	boxVertexData.push_back(0.0f);
	boxVertexData.push_back(Color.x);
	boxVertexData.push_back(Color.y);
	boxVertexData.push_back(Color.z);
	boxVertexData.push_back(Color.w);
	boxVertexData.push_back(SlateTexture ? 1.0f : -1.0f);

	// Bottom right
	boxVertexData.push_back(position.x + size.x);
	boxVertexData.push_back(position.y);
	boxVertexData.push_back(zOrder);
	boxVertexData.push_back(1.0f);
	boxVertexData.push_back(0.0f);
	boxVertexData.push_back(Color.x);
	boxVertexData.push_back(Color.y);
	boxVertexData.push_back(Color.z);
	boxVertexData.push_back(Color.w);
	boxVertexData.push_back(SlateTexture ? 1.0f : -1.0f);

	// Top right
	boxVertexData.push_back(position.x + size.x);
	boxVertexData.push_back(position.y + size.y);
	boxVertexData.push_back(zOrder);
	boxVertexData.push_back(1.0f);
	boxVertexData.push_back(1.0f);
	boxVertexData.push_back(Color.x);
	boxVertexData.push_back(Color.y);
	boxVertexData.push_back(Color.z);
	boxVertexData.push_back(Color.w);
	boxVertexData.push_back(SlateTexture ? 1.0f : -1.0f);

	// Top left
	boxVertexData.push_back(position.x);
	boxVertexData.push_back(position.y + size.y);
	boxVertexData.push_back(zOrder);
	boxVertexData.push_back(0.0f);
	boxVertexData.push_back(1.0f);
	boxVertexData.push_back(Color.x);
	boxVertexData.push_back(Color.y);
	boxVertexData.push_back(Color.z);
	boxVertexData.push_back(Color.w);
	boxVertexData.push_back(SlateTexture ? 1.0f : -1.0f);

	boxGeometry.AppendGeometry(boxVertexData, SlateTexture, GetSlateID(), bStatic);
}