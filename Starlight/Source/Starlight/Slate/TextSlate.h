#pragma once

#include "Starlight/Base.h"
#include "Slate.h"


class Font;

class TextSlate : public Slate
{
public:
	TextSlate();

	virtual void Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry) override;

	TextSlate* SetText(const std::string& text);
	TextSlate* SetFont(const std::shared_ptr<Font>& font);
	TextSlate* SetFont(const std::string& fontSrc);
	TextSlate* SetTextScale(float scale);

private:
	std::shared_ptr<Font> TextFont;
	std::string TextContent;
	float TextScale;
};