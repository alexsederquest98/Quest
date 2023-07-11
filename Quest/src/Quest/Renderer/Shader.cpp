#include "qepch.h"
#include "Quest/Core/Base.h"
#include "Quest/Renderer/Shader.h"
#include "Quest/Renderer/Renderer.h"

#include "Quest/Platform/OpenGL/OpenGLShader.h"

namespace Quest
{
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& vertexFilepath, const std::string& fragmentFilepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLShader>("vertexFilePath", "fragmentFilePath");
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
		}

		return nullptr;
	}
}