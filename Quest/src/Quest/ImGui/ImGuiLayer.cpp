#include "qepch.h"

#include "Quest/ImGui/ImGuiLayer.h"

#include <imgui.h>
#include <imgui_internal.h>

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

#include "Quest/Core/Application.h"

namespace Quest
{
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.BackendFlags |= ImGuiBackendFlags_DockingEnable;
	}

	void ImGuiLayer::OnAttach()
	{

	}

	void ImGuiLayer::OnDetach()
	{

	}

	void ImGuiLayer::OnEvent(Event& e)
	{

	}
}