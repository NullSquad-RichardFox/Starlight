#include "TextSlate.h"
#include "Starlight/Render/Renderer.h"
#include "Starlight/Render/Font.h"


TextSlate::TextSlate()
{
	auto render = Renderer::GetRenderer();
	TextFont = render->GetDefaultFont();
    TextScale = 1.0f;
	Color = glm::vec4(1.f);
}

void TextSlate::Draw(SlateGeometry& boxGeometry, SlateGeometry& textGeometry)
{
    Slate::Draw(boxGeometry, textGeometry);

    std::vector<float> textVertexData;
	textVertexData.reserve(40);
    glm::vec2 position;
	float renderScale = 0.05f * TextScale;
    position.x = Position.x / 540.0f - 1.7777777f;
    position.y = Position.y / 540.0f - 1;
    float zOrder = -1 / (ZOrder + 1) + 1;

	float totalAdvance = 0;
	for (int32 i = 0; i < TextContent.size(); i++)
	{
		glm::vec2 minSize, maxSize, minTexCoords, maxTexCoords;
		TextFont->GetCharSize(TextContent[i], renderScale, minSize, maxSize);
		TextFont->GetCharTextCoords(TextContent[i], minTexCoords, maxTexCoords);

		minSize.x += position.x;
		minSize.y += position.y;
		maxSize.x += position.x;
		maxSize.y += position.y;

		if (i != 0)
		{
			totalAdvance += TextFont->GetAdvance(TextContent[i - 1], TextContent[i], renderScale);
			minSize.x += totalAdvance;
			maxSize.x += totalAdvance;
		}

		// Bottom left
		textVertexData.push_back(minSize.x);
		textVertexData.push_back(minSize.y);
		textVertexData.push_back(zOrder);
		textVertexData.push_back(minTexCoords.x);
		textVertexData.push_back(minTexCoords.y);
		textVertexData.push_back(Color.x);
		textVertexData.push_back(Color.y);
		textVertexData.push_back(Color.z);
		textVertexData.push_back(Color.w);
		textVertexData.push_back(-1.0f);

		// Bottom right
		textVertexData.push_back(maxSize.x);
		textVertexData.push_back(minSize.y);
		textVertexData.push_back(zOrder);
		textVertexData.push_back(maxTexCoords.x);
		textVertexData.push_back(minTexCoords.y);
		textVertexData.push_back(Color.x);
		textVertexData.push_back(Color.y);
		textVertexData.push_back(Color.z);
		textVertexData.push_back(Color.w);
		textVertexData.push_back(-1.0f);

		// Top right
		textVertexData.push_back(maxSize.x);
		textVertexData.push_back(maxSize.y);
		textVertexData.push_back(zOrder);
		textVertexData.push_back(maxTexCoords.x);
		textVertexData.push_back(maxTexCoords.y);
		textVertexData.push_back(Color.x);
		textVertexData.push_back(Color.y);
		textVertexData.push_back(Color.z);
		textVertexData.push_back(Color.w);
		textVertexData.push_back(-1.0f);

		// Top left
		textVertexData.push_back(minSize.x);
		textVertexData.push_back(maxSize.y);
		textVertexData.push_back(zOrder);
		textVertexData.push_back(minTexCoords.x);
		textVertexData.push_back(maxTexCoords.y);
		textVertexData.push_back(Color.x);
		textVertexData.push_back(Color.y);
		textVertexData.push_back(Color.z);
		textVertexData.push_back(Color.w);
		textVertexData.push_back(-1.0f);
	
	}
	textGeometry.AppendGeometry(GetSlateID(), textVertexData, TextFont->GetTexture(), bStatic ? SF_Static : SF_None);
}

TextSlate* TextSlate::SetPosition(glm::vec2 position)
{
	Position = position;
	return this;
}

TextSlate* TextSlate::SetPosition(float x, float y)
{
	Position = glm::vec2(x, y);
	return this;
}

TextSlate* TextSlate::SetColor(glm::vec4 color)
{
	Color = color;
	return this;
}

TextSlate* TextSlate::SetColor(float r, float g, float b, float a)
{
	Color = glm::vec4(r, g, b, a);
	return this;
}

TextSlate* TextSlate::SetZOrder(float zOrder)
{
	ZOrder = zOrder;
	return this;
}

TextSlate* TextSlate::SetText(const std::string& text)
{
	TextContent = text;
	return this;
}

TextSlate* TextSlate::SetFont(const std::shared_ptr<Font>& font)
{
	TextFont = font;
    return this;
}

TextSlate* TextSlate::SetFont(const std::string& fontSrc)
{
	TextFont = std::make_shared<Font>(fontSrc);
	return this;
}

TextSlate* TextSlate::SetTextScale(float scale)
{
	TextScale = scale;
    return this;
}
