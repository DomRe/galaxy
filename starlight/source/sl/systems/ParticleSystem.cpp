///
/// ParticleSystem.cpp
/// starlight
///
/// Created by reworks on 15/01/2018.
/// MIT License.
/// Refer to LICENSE.txt for more details.
///

#include "sl/utils/Random.hpp"
#include "sl/events/EventTypes.hpp"
#include "sl/libs/loguru/loguru.hpp"
#include "sl/events/ParticleEmitEvent.hpp"
#include "sl/components/RenderComponent.hpp"
#include "sl/components/EnabledComponent.hpp"
#include "sl/components/ParticleComponent.hpp"
#include "sl/components/TransformComponent.hpp"

#include "ParticleSystem.hpp"

namespace sl
{
	void ParticleSystem::event(ALLEGRO_EVENT* event, entt::DefaultRegistry& registry)
	{
		switch (event->type)
		{
		case EventTypes::PARTICLE_EMIT_EVENT:
			// Retrieve particle event information.
			ParticleEmitEvent* particleEvent = (ParticleEmitEvent*)event->user.data1;
			auto size = particleEvent->m_textureIDS.size();

			if (size != particleEvent->m_particleCount.size())
			{
				LOG_S(ERROR) << "The number of texture id's and the number of particles are not the same size!";
			}
			else
			{
				for (std::uint32_t i = 0; i < size; ++i)
				{
					// For each particle...
					for (std::uint32_t amountOfParticles = 0; amountOfParticles < particleEvent->m_particleCount[amountOfParticles]; ++amountOfParticles)
					{
						// ...Create an entity of that particle to be rendered to screen.
						entt::DefaultRegistry::entity_type entity = registry.create();
						
						registry.assign<TransformComponent>(entity, particleEvent->m_layer, 0.0f, Rect<float, int>(particleEvent->m_x, particleEvent->m_y, 0, 0));
						registry.assign<ParticleComponent>(entity, Random::random(particleEvent->m_upper, particleEvent->m_lower), Random::random(particleEvent->m_upper, particleEvent->m_lower), particleEvent->m_fade);
						registry.assign<RenderComponent>(entity, 1.0f, particleEvent->m_textureIDS[i]);
						registry.assign<EnabledComponent>(entity);
					}
				}
			}
			
			break;
		}
	}

	void ParticleSystem::update(const double dt, entt::DefaultRegistry& registry)
	{
		// Iterate over ParticleComponent entities.
		registry.view<ParticleComponent, TransformComponent, RenderComponent, EnabledComponent>()
			.each([&](entt::DefaultRegistry::entity_type entity, ParticleComponent& pc, TransformComponent& tc, RenderComponent& rc, EnabledComponent& ec)
		{
			// If the opacity is below 0, i.e. invisible, destroy the entity.
			if (rc.m_opacity <= 0.0f)
			{
				registry.destroy(entity);
			}
			else
			{
				// Otherwise, increment the direction the particle is travelling in and fade it out a little bit more.
				tc.m_rect.m_x += pc.m_direction.m_x;
				tc.m_rect.m_y += pc.m_direction.m_y;

				rc.m_opacity -= pc.m_fade;
			}
		});
	}
}