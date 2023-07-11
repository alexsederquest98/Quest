#include "qepch.h"
#include "Quest/Renderer/Texture.h"
#include "Quest/Renderer/Renderer.h"
#include "Quest/Platform/OpenGL/OpenGLTexture.h"

namespace Quest
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLTexture2D>(path);
		}

		return nullptr;
	}
}