//
//  EventSystem.cpp
//  REngine3
//
//  Created by reworks on 23/08/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#include <SFML/System/Time.hpp>

#include "re/entity/EntityManager.hpp"
#include "re/services/ServiceLocator.hpp"
#include "re/component/EventComponent.hpp"

#include "EventSystem.hpp"

namespace re
{
	EventSystem::~EventSystem()
	{
		m_entitys.clear();
	}

	void EventSystem::AutoSubmit()
	{
		for (auto& it : Locator::Get<EntityManager>()->GetMap())
		{
			if (it.second->Has<EventComponent>())
			{
				AddEntity(it.second);
			}
		}
	}

	void EventSystem::AddEntity(std::shared_ptr<Entity> e)
	{
		e->m_systemIds.emplace("EventSystem", std::type_index(typeid(EventSystem)));
		m_entitys.emplace(e->m_id, e);
	}

	void EventSystem::RemoveEntity(sf::Uint64 e)
	{
		m_entitys.erase(e);
	}

	void EventSystem::Dispatch(EventType type)
	{
		for (auto& it : m_entitys)
		{
			EventComponent* e = it.second->Get<EventComponent>().get();
			if (e->IsSubscribed(type))
			{
				e->OnEvent(type);
			}
		}
	}

	void EventSystem::Clean()
	{
		m_entitys.clear();
	}
}