///
/// testbed.cpp
/// protostar
///
/// Refer to LICENSE.txt for more details.
///

#include <iostream>
#include <protostar/system/Keys.hpp>
#include <protostar/events/KeyUpEvent.hpp>

int main()
{
	protostar::KeyUpEvent e;
	protostar::Keys k;
	k = protostar::Keys::E;

	e.m_keycode = protostar::Keys::A;

	std::cin.get();
}