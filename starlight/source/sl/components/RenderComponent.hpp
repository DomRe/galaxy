///
/// RenderComponent.hpp
/// starlight
///
///  Created by reworks on 12/01/2018.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_RENDERCOMPONENT_HPP_
#define STARLIGHT_RENDERCOMPONENT_HPP_

#include <vector>

#include "sol2/sol_forward.hpp"

namespace sl
{
	class RenderComponent final
	{
	public:
		///
		/// Constructor.
		///
		/// \param table sol::table containing data.
		/// 
		RenderComponent(const sol::table& table);

		///
		/// Move Constructor.
		///
		RenderComponent(RenderComponent&&) = default;

		///
		/// Destructor.
		///
		~RenderComponent() = default;

	public:
		std::vector<unsigned int> m_renderTypes;

	private:
		///
		/// Calls imgui debug functions. Don't call this, done for you by debugmanager.
		///
		void debug();

		///
		/// Default constructor.
		/// Deleted.
		///
		RenderComponent() = delete;

		///
		/// Copy Constructor.
		/// Deleted.
		///
		RenderComponent(const RenderComponent&) = delete;
	};
}

#endif