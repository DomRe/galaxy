///
/// PhysicsSystem.hpp
/// starlight
///
/// Created by reworks on 08/11/2016.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#ifndef STARLIGHT_PHYSICSSYSTEM_HPP_
#define STARLIGHT_PHYSICSSYSTEM_HPP_

#include "sl/types/System.hpp"

namespace sl
{
	class Box2DManager;

	class PhysicsSystem final : public System
	{
	public:
		///
		/// Construct the system.
		///
		/// \param ups Updates per second for physics system.
		/// \param vi Box2D velocity iterations.
		/// \param pi Box2D position iterations.
		///
		PhysicsSystem(float ups, int vi, int pi);

		///
		/// Destructor.
		///
		~PhysicsSystem() override = default;

	private:
		///
		/// Default Constructor.
		/// Deleted.
		///
		PhysicsSystem() = delete;
		
		///
		/// Lets systems recieve events.
		///
		/// \param event ALLEGRO_EVENT passed by application class.
		///
		void event(ALLEGRO_EVENT* event, entt::DefaultRegistry& registry) override;

		///
		/// \brief Update the system.
		///
		/// Dont actually call this, this is called by the world automatically.
		///
		void update(const double dt, entt::DefaultRegistry& registry) override;

	private:
		float m_ups;
		int m_velocityIterations;
		int m_positionIterations;

		Box2DManager* m_manager;
		std::map<std::pair<entt::Entity, entt::Entity>, std::function<void(entt::Entity, entt::Entity)>> m_collisionFunctions;
	};
}

#endif