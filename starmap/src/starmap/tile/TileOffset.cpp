///
/// TileOffset.cpp
/// starmap
///
/// Refer to LICENSE.txt for more details.
///

#include <nlohmann/json.hpp>

#include "TileOffset.hpp"

///
/// Core namespace.
///
namespace starmap
{
	TileOffset::TileOffset() noexcept
		:m_x(0), m_y(0)
	{
	}

	TileOffset::TileOffset(const nlohmann::json& json)
		:m_x(0), m_y(0)
	{
		parse(json);
	}

	void TileOffset::parse(const nlohmann::json& json)
	{
		m_x = json.at("x");
		m_y = json.at("y");
	}

	const int TileOffset::getX() const noexcept
	{
		return m_x;
	}

	const int TileOffset::getY() const noexcept
	{
		return m_y;
	}
}