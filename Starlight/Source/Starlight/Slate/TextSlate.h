#pragma once

#include "Starlight/Base.h"
#include "Slate.h"


class Font;

class TextSlate : public Slate
{
public:
	TextSlate();

	virtual void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry) override;

	TextSlate* SetPosition(glm::vec2 position);
	TextSlate* SetPosition(float x, float y);

	TextSlate* SetColor(glm::vec4 color);
	TextSlate* SetColor(float r, float g, float b, float a = 1.0f);

	TextSlate* SetZOrder(float zOrder);

	TextSlate* SetText(const std::string& text);
	TextSlate* SetFont(const std::shared_ptr<Font>& font);
	TextSlate* SetFont(const std::string& fontSrc);
	TextSlate* SetTextScale(float scale);
	
	inline glm::vec2 GetPosition() const { return Position; }
	inline glm::vec4 GetColor() const { return Color; }
	inline float GetZOrder() const { return ZOrder; }

private:
	glm::vec2 Position;
	glm::vec4 Color;
	float ZOrder;

	std::shared_ptr<Font> TextFont;
	std::string TextContent;
	float TextScale;
};