#include "qepch.h"

#include "Quest/Platform/OpenGL/OpenGLShader.h"

namespace Quest
{
	void OpenGLShader::Bind() const
	{
		// TODO: fix
		glUseProgram(1);
	}

	void OpenGLShader::Unbind() const
	{
		// Pass null (0) to glUseProgram to unbind a shader (i.e. rebind to null)
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const uint32_t& id, int value)
	{
	}

	void OpenGLShader::SetFloat(const uint32_t& id, float value)
	{
	}

	void OpenGLShader::SetFloat2(const uint32_t& id, const glm::vec2& value)
	{
	}

	void OpenGLShader::SetFloat3(const uint32_t& id, const glm::vec3& value)
	{
	}

	void OpenGLShader::SetFloat4(const uint32_t& id, const glm::vec4& value)
	{
	}

	void OpenGLShader::SetMat4(const uint32_t& id, const glm::mat4& value)
	{
	}

	const uint32_t OpenGLShader::GetID() const
	{
		return 0;
	}

}