///
/// ImGuiHelpers.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_UI_IMGUIHELPERS_HPP_
#define GALAXY_UI_IMGUIHELPERS_HPP_

#include <glm/vec3.hpp>
#include <imgui/imgui_stdlib.h>

#include "galaxy/meta/Concepts.hpp"

namespace galaxy
{
	namespace ui
	{
		template<meta::is_class Type>
		[[maybe_unused]] const bool im_draw_class(Type& value, const char* label = "");

		template<meta::is_class Type>
		const bool im_draw_class(Type& value, const char* label)
		{
			static_assert("Unsupported class type.");
			return false;
		}

		template<>
		const bool im_draw_class(glm::vec3& value, const char* label)
		{
			int clicked = 0;

			if (std::strlen(label) > 0)
			{
				ImGui::Text(label);
			}

			ImGui::SetNextItemWidth(60.0f);
			clicked += ImGui::InputFloat("X", &value.x, 0.1f, 1.0f, "%.1f", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::SameLine();

			ImGui::SetNextItemWidth(60.0f);
			clicked += ImGui::InputFloat("Y", &value.y, 0.1f, 1.0f, "%.1f", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);
			ImGui::SameLine();

			ImGui::SetNextItemWidth(60.0f);
			clicked += ImGui::InputFloat("Z", &value.z, 0.1f, 1.0f, "%.1f", ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank);

			return static_cast<bool>(clicked);
		}
	} // namespace ui
} // namespace galaxy

#endif