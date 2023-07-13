#pragma once

#include <string>
#include <unordered_map>
#include "Quest/Core/Base.h"
#include "Quest/Math/Math.h"

namespace Quest
{
	// This is for the 2nd overload of Create
	// if you pass in QE_SHADER_INLINE_TRUE then it will assume
	// that you are passing the shadder in as an std::string to vertexFilepath and fragmentFilepath
	// if you pass in QE_SHADER_INLINE_FALSE, it will assume they are set to the actual file paths of 2 separate
	// shaders
	// NOTE: QE_SHADER_INLINE_FALSE is the default
	#define QE_SHADER_INLINE_TRUE true
	#define QE_SHADER_INLINE_FALSE false
	
	class Shader
	{
	public:
		virtual ~Shader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetIntArray(const std::string& name, int* values, uint32_t count) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetFloat2(const std::string& name, const glm::vec2& value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat3(const std::string& name, const glm::mat3& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		virtual const uint32_t GetID() const = 0;
		virtual const std::string& GetName() const = 0;

		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexFilepath, 
			const std::string& fragmentFilepath, const bool shaderInline = QE_SHADER_INLINE_FALSE);
	};

	class ShaderLibrary
	{
	public:
		void Add(const Ref<Shader>& shader);
		void Add(const std::string& name, const Ref<Shader>& shader);
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		Ref<Shader> Get(const std::string& name);
		bool ShaderExists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}