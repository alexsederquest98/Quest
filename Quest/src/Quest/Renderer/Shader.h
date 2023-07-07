#pragma once

#include <string>
#include "Quest/Core/Base.h"
#include "Quest/Math/Math.h"

namespace Quest
{
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const uint32_t& id, int value) = 0;
		virtual void SetFloat(const uint32_t& id, float value) = 0;
		virtual void SetVec2(const uint32_t& id, const glm::vec2& value) = 0;
		virtual void SetVec3(const uint32_t& id, const glm::vec3& value) = 0;
		virtual void SetVec4(const uint32_t& id, const glm::vec4& value) = 0;
		virtual void SetMat4(const uint32_t& id, const glm::mat4& value) = 0;

		virtual const uint32_t GetID() const = 0;

		static Ref<Shader> Create(const uint32_t& id, const std::string& vertexSource, const std::string& fragmentSource);
	};
}