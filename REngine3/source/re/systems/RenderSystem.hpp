//
//  RenderSystem.hpp
//  REngine3
//
//  Created by reworks on 6/08/2016.
//  Copyright (c) 2016 reworks. All rights reserved.
//

#ifndef RENGINE3_RENDERSYSTEM_HPP_
#define RENGINE3_RENDERSYSTEM_HPP_

#include "re/types/System.hpp"
#include "re/graphics/Group.hpp"

namespace re
{
	class Window;

	class RenderSystem : public System
	{
	public:
		/*
		* IMPORTS: Number of groups. Think "layers". Each group is a layer of entitys to render.
		* EXPORTS: none
		* PURPOSE: Construct the system.
		*/
		RenderSystem(int numOfGroups);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean up the renderer.
		*/
		~RenderSystem() override;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Automatically adds entitys to the system.
		*/
		void AutoSubmit();

		/*
		* IMPORTS: id of entity to add and its component list.
		* EXPORTS: none
		* PURPOSE: Add an entitys components from the system.
		*/
		void AddEntity(std::shared_ptr<Entity> e) override;

		/*
		* IMPORTS: id of entity to remove
		* EXPORTS: none
		* PURPOSE: Remove an entitys components from the system.
		*/
		void RemoveEntity(sf::Uint64 e) override;

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Update the system. Mainly for animations
		*/
		void Update(sf::Time dt);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean up the entitys.
		*/
		void Render(re::Window* window);

		/*
		* IMPORTS: none
		* EXPORTS: none
		* PURPOSE: Clean the system.
		*/
		void Clean();

	private:
		std::vector<Group> m_groups;
	};
}

#endif