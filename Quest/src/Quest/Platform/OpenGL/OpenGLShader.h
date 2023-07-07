#pragma once

#include "Quest/Math/Math.h"
#include "Quest/Renderer/Shader.h"
#include "Quest/Platform/OpenGL/OpenGLBase.h"

namespace Quest
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const uint32_t& id, const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual void SetInt(const uint32_t& id, int value) override;
		virtual void SetFloat(const uint32_t& id, float value) override;
		virtual void SetFloat2(const uint32_t& id, const glm::vec2& value) override;
		virtual void SetFloat3(const uint32_t& id, const glm::vec3& value) override;
		virtual void SetFloat4(const uint32_t& id, const glm::vec4& value) override;
		virtual void SetMat4(const uint32_t& id, const glm::mat4& value) override;
		virtual const uint32_t GetID() const override;
	private:
		void CreateProgram();
		
	};
}