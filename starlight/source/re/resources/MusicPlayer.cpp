///
///  MusicPlayer.cpp
///  starlight
///
///  Created by reworks on 12/10/2017.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#include <allegro5/allegro_audio.h>

#include "sol2/sol.hpp"
#include "re/fs/VFS.hpp"

#include "MusicPlayer.hpp"

namespace sl
{
	MusicPlayer::MusicPlayer(const std::string& script)
	{
		al_restore_default_mixer();
		al_reserve_samples(reserveSamples);

		sol::state lua;
		lua.script(VFS::get()->openAsString(script));
		sol::table music = lua.get<sol::table>("music");

		music.for_each([this](std::pair<sol::object, sol::object> pair)
		{
			m_resourceMap.emplace(pair.first.as<entt::HashedString>(), pair.second.as<sol::table>());
		});
	}

	MusicPlayer::~MusicPlayer()
	{
		clean();
	}

	void MusicPlayer::changeMusicVolume(float volume)
	{
		if (volume > 1.0)
		{ 
			volume = 1.0f;
		}
		
		if (volume < 0.0) 
		{
			volume = 0.0f; 
		}

		for (auto& it : m_resourceMap)
		{
			it.second.setVolume(volume);
		}
	}

	void MusicPlayer::clean()
	{
		m_resourceMap.clear();
	}
}