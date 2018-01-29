///
/// ParticleSystem.hpp
/// starlight
///
///  Created by reworks on 15/01/2018.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_PARTICLESYSTEM_HPP_
#define STARLIGHT_PARTICLESYSTEM_HPP_

#include "sl/types/System.hpp"

namespace sl
{
	class World;

	class ParticleSystem : public System
	{
	public:
		///
		/// Default Constructor.
		///
		ParticleSystem();

		///
		/// Destructor.
		///
		~ParticleSystem() override = default;

	private:
		World* m_world;

	private:
		///
		/// Lets systems recieve events.
		///
		/// \param event ALLEGRO_EVENT passed by application class.
		///
		void event(ALLEGRO_EVENT* event) override;

		///
		/// \brief Update the system.
		///
		/// Dont actually call this, this is called by the world automatically.
		///
		void update(const double dt, entt::DefaultRegistry& registery) override;

		///
		/// Copy Constructor.
		/// Deleted.
		///
		ParticleSystem(const ParticleSystem&) = delete;

		///
		/// Move Constructor.
		/// Deleted.
		///
		ParticleSystem(ParticleSystem&&) = delete;
	};
}

#endif