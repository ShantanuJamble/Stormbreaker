#ifndef SBIMGUIWINDOW_H
#define  SBIMGUIWINDOW_H

#include <string>
#include "ImGui/imgui.h"
#include <ctype.h>          // toupper
#include <limits.h>         // INT_MIN, INT_MAX
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#include "glm/vec3.hpp"
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t

#endif



namespace ImGUI {
	

	class SBImGuiWinodw
	{
	protected:
		std::string m_title;
		ImGuiWindowFlags m_windowFlags;
		bool* m_pOpen;
	
	

	public:
		SBImGuiWinodw(
			std::string& title,
			bool no_titlebar = false,
			bool no_scrollbar = false,
			bool no_menu = false,
			bool no_move = false,
			bool no_resize = false,
			bool no_collapse = false,
			bool no_close = false,
			bool no_nav = false,
			bool no_background = false,
			bool no_bring_to_front = false,
			bool no_docking = false
		);
		~SBImGuiWinodw();

		virtual void AddWidgets() = 0;

		inline std::string GetTitle() const { return m_title; }
	};

}

#endif