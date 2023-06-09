#pragma once

#include "Quest/Core/Base.h"
#include "Quest/Events/Event.h"

namespace Quest
{
	class Layer
	{
	public:
		Layer(const std::string& name = "QuestLayer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetatch() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string GetName() const { return  m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}