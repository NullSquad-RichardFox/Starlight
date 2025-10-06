#pragma once

#include "Base.h"
#include "Slate/SlateGeometry.h"


class Shader;
class Camera;
class Font;
class BufferLayout;
class Texture;
class Layer;

class Renderer
{
public:
	static void Intialize();
	static void Shutdown();

	inline static void OnUpdate(float deltaTime) { if (sRendererInstance) sRendererInstance->OnUpdate_Int(deltaTime); }

	inline static void RenderLayer(const std::shared_ptr<Layer>& layer) { if (sRendererInstance) sRendererInstance->RenderLayer_Int(layer); }

	inline static uint32 GetMaxTextureCount() { return sRendererInstance ? sRendererInstance->MaxTextureCount : 0; }
	inline static const std::shared_ptr<BufferLayout>& GetBufferLayout() { return sRendererInstance ? sRendererInstance->DefaultBufferLayout : nullptr; }
	const std::shared_ptr<Font>& GetDefaultFont() { return DefaultFont; }

	inline static Renderer* GetRenderer() { return sRendererInstance; }

private:
	Renderer();

	void OnUpdate_Int(float deltaTime);
	void RenderLayer_Int(const std::shared_ptr<Layer>& layer);

	void FlushGeometry(const SlateGeometry& geometry, const std::shared_ptr<Shader>& shader);

	inline static Renderer* sRendererInstance = nullptr;
	std::shared_ptr<Shader> TextShader;
	std::shared_ptr<Shader> BoxShader;
	std::shared_ptr<Camera> DefaultCamera;
	std::shared_ptr<Font> DefaultFont;

	std::shared_ptr<BufferLayout> DefaultBufferLayout;

	SlateGeometry BoxGeometry;
	SlateGeometry TextGeometry;

	uint32 MaxTextureCount;
};