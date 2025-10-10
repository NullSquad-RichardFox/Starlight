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

	BoxGeometry = SlateGeometry(MaxTextureCount, DefaultBufferLayout->GetSize());
	TextGeometry = SlateGeometry(MaxTextureCount, DefaultBufferLayout->GetSize());
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
	std::vector<std::shared_ptr<Texture>> textures;
	std::vector<std::pair<void*, uint32>> data;
	geometry.GetFlushData(data, textures);

	for (uint32 i = 0; i < data.size(); i++)
	{
		// Bind textures
		for (uint32 j = 0; j < std::min<uint32>(MaxTextureCount, textures.size() - MaxTextureCount * i); j++)
		{
			textures[i * MaxTextureCount + j]->Bind(j);
		}

		std::shared_ptr<VertexArray> vArray = std::make_shared<VertexArray>();
		vArray->BindBufferLayout(DefaultBufferLayout);
		vArray->AddVertexData(data[i].first, data[i].second);
		vArray->GenerateIndexBuffer();

		shader->Bind();
		shader->SetMat4("uViewProjMat", DefaultCamera->GetViewProjMat());

		RenderUtilities::DrawElements(vArray);
	}
}
