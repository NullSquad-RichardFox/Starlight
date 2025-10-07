#include "Renderer.h"
#include "Font.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "VertexArray.h"
#include "RenderUtilities.h"
#include "Starlight/Core/Layer.h"
#include "Starlight/Slate/SlateGeometry.h"


void Renderer::Intialize()
{
	ASSERT(sRendererInstance == nullptr, "Renderer was already initialized!");
	sRendererInstance = new Renderer();
}

void Renderer::Shutdown()
{
	delete sRendererInstance;
	sRendererInstance = nullptr;
}

Renderer::Renderer()
{
	DefaultCamera = std::make_shared<Camera>(1920.0f / 1080.0f, 1.f);
	DefaultFont = std::make_shared<Font>("Assets/Fonts/arial.ttf");

	TextShader = std::make_shared<Shader>("Assets/Shaders/text.glsl");
	BoxShader = std::make_shared<Shader>("Assets/Shaders/box.glsl");

	BufferLayout textLayout = {
		{ EShaderDataType::Float3, "aPosition" },
		{ EShaderDataType::Float2, "aTexCoord" },
		{ EShaderDataType::Float4, "aColor" },
		{ EShaderDataType::Float,  "aTexID" }
	};

	DefaultBufferLayout = std::make_shared<BufferLayout>(textLayout);

	MaxTextureCount = 32;

	BoxGeometry = SlateGeometry(MaxTextureCount, DefaultBufferLayout);
	TextGeometry = SlateGeometry(MaxTextureCount, DefaultBufferLayout);
}

void Renderer::OnUpdate_Int(float deltaTime)
{
	DefaultCamera->OnUpdate(deltaTime);
}

void Renderer::RenderLayer_Int(const std::shared_ptr<Layer>& layer)
{
	layer->Draw(BoxGeometry, TextGeometry);

	FlushGeometry(BoxGeometry, BoxShader);
	FlushGeometry(TextGeometry, TextShader);
}

void Renderer::FlushGeometry(const SlateGeometry& geometry, const std::shared_ptr<Shader>& shader)
{
	uint32 offset = 0;
	uint32 textureOffset = 0;
	uint32 texturesRendered = 0;
	for (uint32 i = 0; i < geometry.GetFlushPoints().size(); i++)
	{
		uint32 flushPoint = geometry.GetFlushPoints()[i];

		uint32 loopTextures = std::min<uint32>(MaxTextureCount, geometry.GetTextures().size() - texturesRendered);
		for (uint32 j = 0; j < loopTextures; j++)
		{
			geometry.GetTextures()[textureOffset]->Bind(j);
			textureOffset++;
		}
		texturesRendered += loopTextures;

		std::shared_ptr<VertexArray> vArray = std::make_shared<VertexArray>();
		vArray->BindBufferLayout(DefaultBufferLayout);
		vArray->AddVertexData(geometry.GetVertexData().data() + offset, flushPoint - offset);

		shader->Bind();
		shader->SetMat4("uViewProjMat", DefaultCamera->GetViewProjMat());

		RenderUtilities::DrawElements(vArray);

		offset = flushPoint;
	}

	uint32 loopTextures = std::min<uint32>(MaxTextureCount, geometry.GetTextures().size() - texturesRendered);
	for (uint32 j = 0; j < loopTextures; j++)
	{
		geometry.GetTextures()[textureOffset]->Bind(j);
		textureOffset++;
	}
	texturesRendered += loopTextures;

	std::shared_ptr<VertexArray> vArray = std::make_shared<VertexArray>();
	vArray->BindBufferLayout(DefaultBufferLayout);
	vArray->AddVertexData(geometry.GetVertexData().data() + offset, geometry.GetVertexData().size() - offset);

	shader->Bind();
	shader->SetMat4("uViewProjMat", DefaultCamera->GetViewProjMat());

	RenderUtilities::DrawElements(vArray);
}
