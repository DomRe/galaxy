///
/// Renderer.cpp
/// quasar
///
/// Refer to LICENSE.txt for more details.
///

#include <glm/mat4x4.hpp>

#include "qs/core/Shader.hpp"
#include "qs/graphics/ParticleGenerator.hpp"
#include "qs/post/PostEffect.hpp"
#include "qs/shapes/Circle.hpp"
#include "qs/shapes/Line.hpp"
#include "qs/shapes/Point.hpp"
#include "qs/sprite/AnimatedSprite.hpp"
#include "qs/sprite/Sprite.hpp"
#include "qs/sprite/SpriteBatch.hpp"
#include "qs/text/Text.hpp"
#include "qs/texture/RenderTexture.hpp"

#include "Renderer.hpp"

///
/// Core namespace.
///
namespace qs
{
	void Renderer::draw_point(qs::Point& point, qs::Shader& shader)
	{
		point.bind();
		shader.set_uniform("u_point_size", point.get_size());
		shader.set_uniform("u_transform", point.get_transform());

		glDrawElements(GL_POINTS, point.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_line(qs::Line& line, qs::Shader& shader)
	{
		line.bind();
		shader.set_uniform("u_transform", line.get_transform());

		glDrawElements(GL_LINES, line.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_circle(qs::Circle& circle, qs::Shader& shader)
	{
		circle.bind();
		shader.set_uniform("u_transform", circle.get_transform());

		glDrawElements(GL_LINE_LOOP, circle.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_sprite(qs::Sprite& sprite, qs::Shader& shader)
	{
		sprite.bind();

		shader.set_uniform("u_transform", sprite.get_transform());
		shader.set_uniform("u_opacity", sprite.opacity());
		shader.set_uniform<float>("u_width", static_cast<float>(sprite.get_width()));
		shader.set_uniform<float>("u_height", static_cast<float>(sprite.get_height()));

		glDrawElements(GL_TRIANGLES, sprite.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_animated_sprite(qs::AnimatedSprite& sprite, qs::Shader& shader)
	{
		sprite.bind();

		shader.set_uniform("u_transform", sprite.get_transform());
		shader.set_uniform("u_opacity", sprite.opacity());
		shader.set_uniform<float>("u_width", static_cast<float>(sprite.get_width()));
		shader.set_uniform<float>("u_height", static_cast<float>(sprite.get_height()));

		glDrawElements(GL_TRIANGLES, sprite.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_sprite_batch(qs::SpriteBatch& sprite_batch, qs::Shader& shader)
	{
		sprite_batch.bind();

		shader.set_uniform<float>("u_width", static_cast<float>(sprite_batch.get_width()));
		shader.set_uniform<float>("u_height", static_cast<float>(sprite_batch.get_height()));

		glDrawElements(GL_TRIANGLES, sprite_batch.get_used_index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_sprite_to_texture(qs::Sprite* sprite, qs::RenderTexture& target, qs::Shader& shader)
	{
		shader.set_uniform("u_projection", target.get_proj());

		sprite->bind();
		shader.set_uniform("u_transform", sprite->get_transform());
		shader.set_uniform<float>("u_width", static_cast<float>(sprite->get_width()));
		shader.set_uniform<float>("u_height", static_cast<float>(sprite->get_height()));

		glDrawElements(GL_TRIANGLES, sprite->index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_text(qs::Text& text, qs::Shader& shader)
	{
		text.bind();

		shader.set_uniform("u_colour", text.get_colour());
		shader.set_uniform<float>("u_width", static_cast<float>(text.get_batch_width()));
		shader.set_uniform<float>("u_height", static_cast<float>(text.get_batch_height()));

		glDrawElements(GL_TRIANGLES, text.index_count(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::draw_particles(qs::ParticleGenerator& particle_gen, qs::Shader& shader)
	{
		if (!particle_gen.finished())
		{
			particle_gen.bind();

			auto* current = particle_gen.get_instance();

			shader.set_uniform<float>("u_width", current->get_width());
			shader.set_uniform<float>("u_height", current->get_height());

			glDrawElementsInstanced(GL_TRIANGLES, particle_gen.gl_index_count(), GL_UNSIGNED_INT, nullptr, particle_gen.amount());
		}
	}

	void Renderer::add_post_effect(qs::PostEffect* effect)
	{
		m_effects.push_back(effect);
	}

	std::span<qs::PostEffect*> Renderer::get_post_effects()
	{
		return m_effects;
	}

	void Renderer::clear_post_effects()
	{
		m_effects.clear();
	}
} // namespace qs