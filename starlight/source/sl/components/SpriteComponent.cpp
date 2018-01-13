///
///  SpriteComponent.cpp
///  starlight
///
///  Created by reworks on 12/08/2016.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#include <algorithm>

#include "sol2/sol.hpp"
#include "imgui/imgui_impl_a5.h"
#include "sl/graphics/TextureAtlas.hpp"
#include "sl/services/ServiceLocator.hpp"
#include "sl/components/TransformComponent.hpp"

#include "SpriteComponent.hpp"

namespace sl
{
	SpriteComponent::SpriteComponent(const sol::table& table)
	{
		m_spriteName = entt::HashedString(table.get<const char*>("spriteName"));
	}

	void SpriteComponent::debug()
	{
		//ImGui::stl::InputText("Sprite Name (in atlas):", &m_spriteName, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_CharsNoBlank | ImGuiInputTextFlags_EnterReturnsTrue);
	}
}