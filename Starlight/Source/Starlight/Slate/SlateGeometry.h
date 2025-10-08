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

	// Needs to be as fast as possible
	void AppendGeometry(FUUID slateID, const std::vector<float>& data, const std::shared_ptr<Texture>& texture, uint32 slateFlags = 0)
	{
		if (!data.size()) return;

		// Slate already loaded in memory
		if (auto it = SlateIndexRegistry.find(slateID); it != SlateIndexRegistry.end())
		{
			// Static data does not change
			if ((slateFlags & SF_Static) == SF_Static) continue;

			for (uint32 i = 0; i < CellSize; i++)
			{
				VertexDataCache[it->second + i] = data[i];
			}
		
			return;
		}

		// Add slate to the memory
		uint32 index;
		if (FreeSlotIndices.size() == 0)
		{
			uint32 index = VertexDataCache.size();

		}
		else
		{
			uint32 index = FreeSlotIndices[0];
			FreeSlotIndices.erase(FreeSlotIndices.begin());
		}

		VertexDataCache.insert(VertexDataCache.end(), data.begin(), data.end());
		SlateIndexRegistry[slateID] = index;

		if (texture)
		{
			Textures[index] = texture;
		}

		RecacheFlushData();
	}

	// Can be slower
	void EraseGeometry(FUUID slateID)
	{
		if (auto it = SlateIndexRegistry.find(slateID); it != SlateIndexRegistry.end())
		{
			// We do not clear data only set it to be clear when new data is added
			FreeSlotIndices.push_back(it->second);
			if (auto it = Textures.find(it->second); it != Textures.end())
				Textures.erase(it);

			RecacheFlushData();
		}
	}

	// Needs to be fast
	void GetFlushData(std::vector<std::vector<std::pair<void*, uint32>>>& vData, std::vector<Texture>& textures)
	{
		vData = CachedFlushData;
		textures.reserve(Textures.size());
		for (const auto& [id, texture] : Textures)
			textures.push_back(texture);
	}

private:
	void RecacheFlushData()
	{
		CachedFlushData.clear();
		CachedFlushData.reserve(Textures.size() / MaxTextureCount + 1);
		
		uint32 prevIndex = 0; 
		uint32 currentTextureCount = 0;
		std::vector<std::pair<void*, uint32>> flushData;
		
		// Itter through all data
		for (uint32 i = 0; i < VertexDataCache.size() / CellSize; i++)
		{
			// Handle hole 
			if (auto it = std::find(FreeSlotIndices.begin(), FreeSlotIndices.end(), i * CellSize); it != FreeSlotIndices.end())
			{
				if (prevIndex != 0 && prevIndex + CellSize == i * CellSize)
				{
					prevIndex = i * CellSize;
					continue;
				}

				flushData.push_back(std::make_pair<void*, uint32>(VertexDataCache.data() + prevIndex, i * CellSize - prevIndex));
			}

			// Handle textures
			if (auto it = Textures.find(i * CellSize); it != Textures.end())
			{
				currentTextureCount++;
				if (currentTextureCount == MaxTextureCount)
				{
					CachedFlushData.push_back(flushData);
					flushData.clear();
					currentTextureCount = 0;
				}
			}
		}
	}

	std::vector<float> VertexDataCache;
	std::vector<uint32> FreeSlotIndices;
	std::unordered_map<FUUID, uint32> SlateIndexRegistry;
	std::map<uint32, Texture> Textures;

	std::vector<std::vector<std::pair<void*, uint32>>> CachedFlushData;

	uint32 MaxTextureCount = 32;
	uint32 BufferSize = 10;
	uint32 CellSize = BufferSize * 4;
};