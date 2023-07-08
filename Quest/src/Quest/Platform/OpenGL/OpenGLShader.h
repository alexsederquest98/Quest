#pragma once

#include "Quest/Math/Math.h"
#include "Quest/Renderer/Shader.h"
#include "Quest/Platform/OpenGL/OpenGLBase.h"

#include <unordered_map>

namespace Quest
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetInt(const std::string& name, int value) override;
		virtual void SetFloat(const std::string& name, float value) override;
		virtual void SetVec2(const std::string& name, const glm::vec2& value) override;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) override;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) override;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) override;
		virtual const uint32_t GetID() const override;
	private:
		void CreateProgram();

	private:
		uint32_t m_RendererID;
		std::string m_FilePath;
		std::string m_Name;

		std::unordered_map<GLenum, std::string> m_Sources;
		
	};
}