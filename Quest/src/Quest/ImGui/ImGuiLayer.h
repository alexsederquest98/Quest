#pragma once

#include "Quest/Core/Layer.h"

#include "Quest/Events/ApplicationEvent.h"
#include "Quest/Events/KeyEvent.h"
#include "Quest/Events/MouseEvent.h"

namespace Quest
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void BeginFrame();
		void EndFrame();
		
		void BlockEvents(bool block) { m_BlockEvents = block; }

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};
}