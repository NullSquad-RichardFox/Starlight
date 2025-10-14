#pragma once

#include "Starlight/Base.h"


class Texture;

enum ESlateFlags : uint32
{
	SF_None 		= 0b0000000000000000,
	SF_Static 		= 0b0000000000000001
};

class SlateGeometry
{
public:
	SlateGeometry();
	SlateGeometry(uint32 maxTextureCount, uint32 bufferSize);

	void AppendGeometry(FUUID slateID, const std::vector<float>& data, const std::shared_ptr<Texture>& texture, uint32 slateFlags = 0);
	void EraseGeometry(FUUID slateID);

	void GetFlushData(std::vector<std::pair<void*, uint32>>& vData, std::vector<std::shared_ptr<Texture>>& textures) const;

private:
	void RecacheFlushData();

	std::vector<float> VertexDataCache;
	std::unordered_map<uint32, uint32> CellSizes;
	std::unordered_map<FUUID, uint32> SlateIndexRegistry;
	std::map<uint32, uint32> TextureRegistry;
	std::vector<std::shared_ptr<Texture>> TextureStorage;

	std::vector<std::pair<void*, uint32>> CachedFlushData;

	uint32 MaxTextureCount = 32;
	uint32 BufferSize = 10;
};