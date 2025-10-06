#pragma once

#include "Starlight/Base.h"


class Texture;
class BufferLayout;

enum ESlateFlags : uint32
{
	SF_None = 0b0000000000000001
};

class SlateGeometry
{
public:
	SlateGeometry();
	SlateGeometry(uint32 maxTextureCount, const std::shared_ptr<BufferLayout>& layout);

	void AppendGeometry(const std::vector<float>& vertexData, const std::shared_ptr<Texture>& texture, FUUID slateID, bool bStatic = false, uint32 slateFlags = 0);
	void Clear();

	const std::vector<float>& GetVertexData() const { return VertexData; }
	const std::vector<std::shared_ptr<Texture>>& GetTextures() const { return Textures; }
	const std::vector<uint32>& GetFlushPoints() const { return FlushPoints; }

private:
	std::vector<float> VertexData;
	std::vector<std::shared_ptr<Texture>> Textures;
	std::vector<uint32> FlushPoints;

	uint32 MaxTexureCount;
	std::shared_ptr<BufferLayout> DefaultLayout;
	uint32 CurrentTextureCount;
	std::unordered_map<FUUID, uint32> SlateGeomertyRegistry;
};