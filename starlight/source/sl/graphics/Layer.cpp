///
///  Layer.cpp
///  starlight
///
///  Created by reworks on 11/08/2016.
///  Copyright (c) 2018+ reworks.
///  Refer to LICENSE.txt for more details.
///

#include "Layer.hpp"

namespace re
{
	Layer::Layer(unsigned int defaultAlloc)
		:m_defaultAlloc(defaultAlloc)
	{
		clean();
	}

	Layer::~Layer()
	{
		m_renderables.clear();
	}

	void Layer::render()
	{
		for (auto r : m_renderables)
		{
			r->render();
		}
	}

	void Layer::insert(Renderable* rc)
	{
		m_renderables.push_back(rc);
	}

	void Layer::clean()
	{
		m_renderables.clear();
		m_renderables.reserve(20);
	}
}