#include "imgui.h"
#include "SBImGuiWindow.h"


//void ImGUI::TestWindow(bool* p_open)
//{
//	IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing dear imgui context. Refer to examples app!"); // Exceptionally add an extra assert here for people confused with initial dear imgui setup
//
//	// We specify a default position/size in case there's no data in the .ini file. Typically this isn't required! We only do it to make the Demo applications a little more welcoming.
//	
//
//	// Demonstrate the various window flags. Typically you would just use the default!
//	static bool no_titlebar = false;
//	static bool no_scrollbar = false;
//	static bool no_menu = false;
//	static bool no_move = false;
//	static bool no_resize = false;
//	static bool no_collapse = false;
//	static bool no_close = false;
//	static bool no_nav = false;
//	static bool no_background = false;
//	static bool no_bring_to_front = false;
//	static bool no_docking = false;
//
//	ImGuiWindowFlags window_flags = 0;
//	if (no_titlebar)        window_flags |= ImGuiWindowFlags_NoTitleBar;
//	if (no_scrollbar)       window_flags |= ImGuiWindowFlags_NoScrollbar;
//	if (!no_menu)           window_flags |= ImGuiWindowFlags_MenuBar;
//	if (no_move)            window_flags |= ImGuiWindowFlags_NoMove;
//	if (no_resize)          window_flags |= ImGuiWindowFlags_NoResize;
//	if (no_collapse)        window_flags |= ImGuiWindowFlags_NoCollapse;
//	if (no_nav)             window_flags |= ImGuiWindowFlags_NoNav;
//	if (no_background)      window_flags |= ImGuiWindowFlags_NoBackground;
//	if (no_bring_to_front)  window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
//	if (no_docking)         window_flags |= ImGuiWindowFlags_NoDocking;
//	if (no_close)           p_open = NULL; // Don't pass our bool* to Begin
//
//	
//	
//	
//
//	ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);
//	ImGui::Spacing();
//	ImGui::NewLine();
//	glm::vec3 scale{ 0,0,0 };
//	ImGui::SliderFloat3("test", &scale.x, 0, 100);
//	ImGui::Text("%f %f %f",10.0f, 10.0f,10.0f);
//
//	
//}


ImGUI::SBImGuiWinodw::SBImGuiWinodw(std::string& title, bool no_titlebar /*= false*/, bool no_scrollbar /*= false*/, 
	bool no_menu /*= false*/, bool no_move /*= false*/, bool no_resize /*= false*/, bool no_collapse /*= false*/,
	bool no_close /*= false*/, bool no_nav /*= false*/, bool no_background /*= false*/, bool no_bring_to_front /*= false*/,
	bool no_docking /*= false */)
	:
	m_title(title),
	m_windowFlags(0),
	m_pOpen(nullptr)

{
	if (no_titlebar)        m_windowFlags |= ImGuiWindowFlags_NoTitleBar;
	if (no_scrollbar)       m_windowFlags |= ImGuiWindowFlags_NoScrollbar;
	if (!no_menu)           m_windowFlags |= ImGuiWindowFlags_MenuBar;
	if (no_move)            m_windowFlags |= ImGuiWindowFlags_NoMove;
	if (no_resize)          m_windowFlags |= ImGuiWindowFlags_NoResize;
	if (no_collapse)        m_windowFlags |= ImGuiWindowFlags_NoCollapse;
	if (no_nav)             m_windowFlags |= ImGuiWindowFlags_NoNav;
	if (no_background)      m_windowFlags |= ImGuiWindowFlags_NoBackground;
	if (no_bring_to_front)  m_windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	if (no_docking)         m_windowFlags |= ImGuiWindowFlags_NoDocking;
	if (no_close)           m_pOpen = NULL; // Don't pass our bool* to Begin


	ImVec2 main_viewport_pos = ImGui::GetMainViewport()->Pos;
	ImGui::SetNextWindowPos(ImVec2(main_viewport_pos.x + 650, main_viewport_pos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);
}


