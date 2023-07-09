#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"
#include "Quest/Core/Timestep.h"

namespace Quest
{
	class Layer
	{
	public:
		Layer(const std::string& name = "QuestLayer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnEvent(Event& event) {}
		virtual void OnImGuiRender() {}

		const std::string GetName() const { return  m_DebugName; }
	protected:
		std::string m_DebugName;
		bool m_Enabled;
	};
}