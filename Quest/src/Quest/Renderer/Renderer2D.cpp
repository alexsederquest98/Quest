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
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DData s_Data;

	void Renderer2D::Init()
	{
		s_Data.QuadVertexArray = VertexArray::Create();
		float quadVertices[] = {
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f // top left 
		};

		Ref<VertexBuffer> quadVertexBuffer = VertexBuffer::Create(quadVertices, sizeof(quadVertices));
		quadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" }
		});
		s_Data.QuadVertexArray->AddVertexBuffer(quadVertexBuffer);

		uint32_t quadIndices[] = { 0, 1, 3, 1, 2, 3 };
		Ref<IndexBuffer> quadIndexBuffer = IndexBuffer::Create(quadIndices, sizeof(quadIndices) / sizeof(uint32_t));
		s_Data.QuadVertexArray->SetIndexBuffer(quadIndexBuffer);

		s_Data.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		s_Data.TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetInt("u_Texture", 0);
	}
	void Renderer2D::Shutdown()
	{

	}
	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		s_Data.TextureShader->Bind();
		s_Data.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
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
		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.WhiteTexture->Bind();

		// transform = translation * rotation * scale
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * 
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawElements(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		s_Data.TextureShader->SetFloat4("u_Color", color);
		s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);
		s_Data.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);
		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawElements(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawElements(s_Data.QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		s_Data.TextureShader->SetFloat4("u_Color", tintColor);
		s_Data.TextureShader->SetFloat("u_TilingFactor", tilingFactor);
		texture->Bind();

		// transform = translation * rotation * scale
		// TODO: add rotation here
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
			glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		s_Data.TextureShader->SetMat4("u_Transform", transform);

		s_Data.QuadVertexArray->Bind();
		RenderCommand::DrawElements(s_Data.QuadVertexArray);
	}
}