///
/// KeyCharEvent.hpp
/// protostar
///
/// Refer to LICENSE.txt for more details.
///

#ifndef PROTOSTAR_KEYCHAREVENT_HPP_
#define PROTOSTAR_KEYCHAREVENT_HPP_

#include "protostar/system/Keys.hpp"

///
/// Core namespace.
///
namespace pr
{
	///
	/// Event for use with unicode characters, not KeyDown, etc...
	///
	struct KeyCharEvent final
	{
		///
		/// Default constructor.
		///
		KeyCharEvent();

		///
		/// Argument constructor.
		///
		/// \param keycode Code of the key pressed.
		/// \param unichar Unicode character pressed.
		///
		KeyCharEvent(const pr::Keys keycode, const int unichar);

		///
		/// Copy constructor.
		///
		KeyCharEvent(const KeyCharEvent&) = default;

		///
		/// Move constructor.
		///
		KeyCharEvent(KeyCharEvent&&) = default;

		///
		/// Copy assignment operator.
		///
		KeyCharEvent& operator=(const KeyCharEvent&) = default;

		///
		/// Move assignment operator.
		///
		KeyCharEvent& operator=(KeyCharEvent&&) = default;

		///
		/// Default destructor.
		///
		~KeyCharEvent() = default;

		///
		/// Keycode for the key that was pressed.
		///
		pr::Keys m_keycode;

		///
		/// Unicode character for use with unicode strings.
		///
		int m_unichar;
	};
} // namespace pr

#endif