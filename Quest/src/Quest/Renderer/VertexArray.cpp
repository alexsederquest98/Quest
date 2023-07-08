#include "qepch.h"

#include "Quest/Core/Base.h"
#include "Quest/Renderer/Renderer.h"
#include "Quest/Renderer/VertexArray.h"

#include "Quest/Platform/OpenGL/OpenGLVertexArray.h"

namespace Quest
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLVertexArray>();
		}

		return nullptr;
	}
}