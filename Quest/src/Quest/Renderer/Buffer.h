#pragma once

namespace Quest
{
	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		//virtual void SetData();

		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		//virtual void SetData();

		//static Ref<IndexBuffer> Create(uint32_t size);
		static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t size);
	};
}