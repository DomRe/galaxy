///
/// World.cpp
/// starlight
///
/// Created by reworks on 09/07/2016.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include "sl/fs/VirtualFS.hpp"
#include "sl/tags/CameraTag.hpp"
#include "sl/core/ServiceLocator.hpp"
#include "sl/components/RenderComponent.hpp"
#include "sl/components/PhysicsComponent.hpp"
#include "sl/components/ParticleComponent.hpp"
#include "sl/components/ParallaxComponent.hpp"
#include "sl/components/AnimationComponent.hpp"
#include "sl/components/TransformComponent.hpp"

#include "World.hpp"

namespace sl
{
	World::World()
	:m_scriptFolderPath(""), m_textureFolderPath("")
	{
		// Set up lua and register all the libraries we need.
		m_lua.open_libraries(sol::lib::base, sol::lib::math, sol::lib::os, sol::lib::package, sol::lib::string, sol::lib::table, sol::lib::utf8);

		// Register the library components and tags.
		registerComponent<AnimationComponent>("AnimationComponent");
		registerComponent<ParallaxComponent>("ParallaxComponent");
		registerComponent<ParticleComponent>("ParticleComponent");
		registerComponent<PhysicsComponent>("PhysicsComponent");
		registerComponent<RenderComponent>("RenderComponent");
		registerComponent<TransformComponent>("TransformComponent");

		registerTag<CameraTag>("CameraTag");
	}

	World::~World()
	{
		// Clean up data.
		m_tagAssign.clear();
		m_componentAssign.clear();
		m_systems.clear();
		m_registry.reset();
	}

	void World::createEntity(const std::string& script)
	{
		// Set up a lua state to load the script into.
		sol::state loader;
		loader.script(Locator::virtualFS->openAsString(script));
		
		// Create entity.
		entt::DefaultRegistry::entity_type entity = m_registry.create();
		sol::table components = loader.get<sol::table>("entity");

		// Loop over components
		if (!components.empty())
		{
			components.for_each([&](std::pair<sol::object, sol::object> pair)
			{
				// Use the assign function to create components for entities without having to know the type.
				m_componentAssign[entt::HashedString{ pair.first.as<const char*>() }](entity, pair.second.as<sol::table>());

				// Then if its the physics component, we set up the fixture collision callback entity.
				if (pair.first.as<const char*>() == "PhysicsComponent")
				{
					m_registry.get<PhysicsComponent>(entity).setFixtureEntity(entity);
				}
			});
		}

		// Loop over tags and assign.
		sol::table tags = components.get<sol::table>("tags");
		if (!tags.empty())
		{
			tags.for_each([&](std::pair<sol::object, sol::object> pair)
			{
				// Use the assign function to create tags for entities without having to know the type.
				m_tagAssign[entt::HashedString{ pair.first.as<const char*>() }](entity, pair.second.as<sol::table>());
			});
		}
	}

	void World::createEntities(const std::string& batchScript)
	{	
		// This just batch calls createEntity on a list of entitys.
		sol::state loader;
		loader.script(Locator::virtualFS->openAsString(batchScript));

		sol::table entityList = loader.get<sol::table>("entityList");
		entityList.for_each([&](std::pair<sol::object, sol::object> pair)
		{
			// For each entity in list, create that entity.
			createEntity(pair.second.as<std::string>());
		});
	}

	void World::event(ALLEGRO_EVENT* event)
	{
		// Process systems events.
		for (auto& systemPair : m_systems)
		{
			systemPair.second->event(event, m_registry);
		}
	}

	void World::update(const double dt)
	{
		// Update systems.
		for (auto& systemPair : m_systems)
		{
			systemPair.second->update(dt, m_registry);
		}
	}
}