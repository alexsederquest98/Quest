#include "qepch.h"

#include "Quest/Core/Base.h"
#include "Quest/Renderer/Buffer.h"
#include "Quest/Renderer/Renderer.h"

#include "Quest/Platform/OpenGL/OpenGLBuffer.h"

namespace Quest
{
	// VERTEX BUFFER
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLVertexBuffer>(size);
		}

		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLVertexBuffer>(vertices, size);
		}

		return nullptr;
	}

	// INDEX BUFFER
	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RendererAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLIndexBuffer>(indices, size);
		}

		return nullptr;
	}
}