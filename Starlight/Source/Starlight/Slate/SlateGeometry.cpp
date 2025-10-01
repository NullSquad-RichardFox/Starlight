#include "SlateGeometry.h"
#include "Render/VertexArray.h"


SlateGeometry::SlateGeometry()
{
	MaxTexureCount = 0;
	DefaultLayout = nullptr;
}

SlateGeometry::SlateGeometry(uint32 maxTextureCount, const std::shared_ptr<BufferLayout>& layout)
{
	MaxTexureCount = maxTextureCount;
	DefaultLayout = layout;
	CurrentTextureCount = 0;
}

uint32 SlateGeometry::AppendGeometry(const std::vector<float>& vertexData, const std::shared_ptr<Texture>& texture, uint32 slateID, bool bStatic)
{
	ASSERT(DefaultLayout && MaxTexureCount, "Slate geometry was constructed incorectly, do not use default constructor!");

	// First draw call
	if (slateID == std::numeric_limits<uint32>::max())
	{
		if (!vertexData.size()) return slateID;

		ASSERT(vertexData.size() % DefaultLayout->GetSize() == 0, "Vertex data does not match the buffer layout!");

		uint32 offset = VertexData.size();
		VertexData.reserve(offset + vertexData.size());
		VertexData.insert(VertexData.end(), vertexData.begin(), vertexData.end());

		if (texture)
		{
			Textures.push_back(texture);
			uint32 bufferSize = DefaultLayout->GetSize();
			uint32 vCount = vertexData.size() / bufferSize;
			for (uint32 i = 0; i < vCount; i++)
			{
				if (VertexData[offset + bufferSize * i + 9] == 1.0f)
				{
					VertexData[offset + bufferSize * i + 9] = CurrentTextureCount;
				}
			}

			CurrentTextureCount++;
			if (CurrentTextureCount == MaxTexureCount)
			{
				FlushPoints.push_back(offset);
				CurrentTextureCount = 0;
			}
		}

		return offset;
	}

	// Subsequent draw calls
	
	// Static slates cannot change form, so we use old data
	if (bStatic) return slateID;

	for (uint32 i = 0; i < vertexData.size(); i++)
	{
		if (VertexData[slateID + i] == vertexData[i])
			continue;

		VertexData[slateID + i] = vertexData[i];
	}

	return slateID;
}

void SlateGeometry::Clear()
{
	VertexData.clear();
	Textures.clear();
	FlushPoints.clear();
	CurrentTextureCount = 0;
}