///
/// LightSource.cpp
/// quasar
///
/// Refer to LICENSE.txt for more details.
///

#include "LightSource.hpp"

///
/// Core namespace.
///
namespace qs
{
	LightSource::LightSource() noexcept
		:m_zLevel(0.0f), m_pos(0.0f, 0.0f), m_falloff(0.0f, 0.0f, 1.0f), m_lightColour(1.0f), m_ambientColour(1.0f)
	{
	}
}