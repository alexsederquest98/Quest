#include "qepch.h"
#include "Quest/Renderer/Renderer2D.h"

#include "Quest/Renderer/RenderCommand.h"
#include "Quest/Renderer/VertexArray.h"
#include "Quest/Renderer/Shader.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Quest
{
	struct Renderer2DData
	{
		Ref<VertexArray> QuadVertexArray;
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();
		float quadVertices[] = {
			 0.5f,  0.5f, 0.0f, // top right
			 0.5f, -0.5f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f  // top left 
		};

		Ref<VertexBuffer> quadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVertexBuffer->SetLayout({
			{ ShaderDataType::Vec3, "a_Position" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t quadIndices[] = { 0, 1, 3, 1, 2, 3 };
		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		s_Data.FlatColorShader = Shader::Create("assets/shaders/FlatColorShader.glsl");
	}
	void Renderer2D::Shutdown()
	{

	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
	}
	void Renderer2D::EndScene()
	{
	}
	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		s_Data.FlatColorShader->Bind();
		s_Data.FlatColorShader->SetFloat4("u_Color", color);

		// transform = translation * rotation * scale
		// TODO: add rotation here
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.FlatColorShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawElements(s_Data.QuadVertexArray);
	}
}