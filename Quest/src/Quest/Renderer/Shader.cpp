#include "qepch.h"
#include "Quest/Core/Base.h"
#include "Quest/Renderer/Shader.h"
#include "Quest/Renderer/Renderer.h"

#include "Quest/Platform/OpenGL/OpenGLShader.h"

namespace Quest
{
	// SHADER
	Ref<Shader> Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLShader>(filepath);
		}

		return nullptr;
	}

	Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexFilepath, const std::string& fragmentFilepath, const bool shaderInline)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::NONE:	QE_CORE_ASSERT(false, "RenderAPI::NONE is not supported"); return nullptr;
		case RendererAPI::API::OPENGL:	return CreateRef<OpenGLShader>(name, vertexFilepath, fragmentFilepath, shaderInline);
		}

		return nullptr;
	}


	// SHADER LIBRARY
	void ShaderLibrary::Add(const Ref<Shader>& shader)
	{
		auto& name = shader->GetName();
		Add(name, shader);
	}
	
	void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
	{
		QE_CORE_ASSERT(!ShaderExists(name), "Shader already exists");
		m_Shaders[name] = shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::Create(filepath);
		Add(name, shader);
		return shader;
	}

	Ref<Shader> ShaderLibrary::Get(const std::string& name)
	{
		QE_CORE_ASSERT(ShaderExists(name), "Shader not found");
		return m_Shaders[name];
	}

	bool ShaderLibrary::ShaderExists(const std::string& name) const
	{
		return m_Shaders.find(name) != m_Shaders.end();
	}
}