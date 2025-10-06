#pragma once

#include "Starlight/Base.h"


typedef uint32 GLenum;

enum class EShaderDataType
{
	None,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	int32,
	Int2,
	Int3,
	Int4,
	Bool
};

class Utils
{
public:
	static uint32 GetShaderDataTypeSize(EShaderDataType type);
	static uint32 GetShaderDataTypeComponentCount(EShaderDataType type);
	static GLenum GetShaderDataTypeToOpenGLBaseType(EShaderDataType type);
};

struct BufferElement
{
	std::string Name;
	EShaderDataType Type;
	uint32 Size;
	uint32 Offset;
	bool bNormalized;

	BufferElement(EShaderDataType type, const std::string& name, bool bNormalized = false)
		:Name(name), Type(type), Size(Utils::GetShaderDataTypeSize(type)), Offset(0), bNormalized(bNormalized) {}
};

class BufferLayout
{
public:
	BufferLayout() :Elements({}), Stride(0), Size(0) {}
	BufferLayout(const std::initializer_list<BufferElement>& elements)
		:Elements(elements), Stride(0), Size(0)
	{
		CalculateOffsetAndStride();
	}

	inline const std::vector<BufferElement>& GetElements() const { return Elements; }
	inline const uint32 GetStride() const { return Stride; }
	inline const uint32 GetSize() const { return Size; }

	std::vector<BufferElement>::iterator begin() { return Elements.begin(); }
	std::vector<BufferElement>::iterator end() { return Elements.end(); }
	std::vector<BufferElement>::const_iterator begin() const { return Elements.begin(); }
	std::vector<BufferElement>::const_iterator end() const { return Elements.end(); }

private:
	void CalculateOffsetAndStride()
	{
		uint32 offset = 0;
		for (auto& element : Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			Stride += element.Size;

			Size += Utils::GetShaderDataTypeComponentCount(element.Type);
		}
	}

	std::vector<BufferElement> Elements;
	uint32 Stride;
	uint32 Size;
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddVertexData(const float* vertexData, uint32 size);
	void BindBufferLayout(const std::shared_ptr<BufferLayout>& bufferLayout);

	uint32 GetIndexCount() const { return IndexCount; }

private:
	std::shared_ptr<BufferLayout> ArrayLayout;
	uint32 ArrayID;
	uint32 VertexBufferID;
	uint32 IndexBufferID;
	uint32 IndexCount;
};