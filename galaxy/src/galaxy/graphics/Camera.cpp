///
/// Camera.cpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#include <nlohmann/json.hpp>

#include "Camera.hpp"

namespace galaxy
{
	namespace graphics
	{
		Camera::Camera() noexcept
		    : Serializable {this}, m_dirty {true}, m_origin {0.0f, 0.0f, 0.0f}, m_scaling {1.0f}, m_translation {1.0f}, m_model {1.0f}, m_identity_matrix {1.0f}, m_scale {1.0f}, m_pos {0.0f, 0.0f}, m_move_up {false}, m_move_down {false}, m_move_left {false}, m_move_right {false}, m_speed {1.0f}, m_width {1.0f}, m_height {1.0f}, m_projection {1.0f}
		{
		}

		Camera::Camera(const nlohmann::json& json) noexcept
		    : Serializable {this}, m_dirty {true}, m_origin {0.0f, 0.0f, 0.0f}, m_scaling {1.0f}, m_translation {1.0f}, m_model {1.0f}, m_identity_matrix {1.0f}, m_scale {1.0f}, m_pos {0.0f, 0.0f}, m_move_up {false}, m_move_down {false}, m_move_left {false}, m_move_right {false}, m_speed {1.0f}, m_width {1.0f}, m_height {1.0f}, m_projection {1.0f}
		{
			create(0.0f, json.at("width"), json.at("height"), 0.0f);
			m_speed = json.at("speed");
		}

		Camera::Camera(const float left, const float right, const float bottom, const float top, const float speed) noexcept
		    : Serializable {this}, m_dirty {true}, m_origin {0.0f, 0.0f, 0.0f}, m_scaling {1.0f}, m_translation {1.0f}, m_model {1.0f}, m_identity_matrix {1.0f}, m_scale {1.0f}, m_pos {0.0f, 0.0f}, m_move_up {false}, m_move_down {false}, m_move_left {false}, m_move_right {false}, m_speed {speed}, m_width {1.0f}, m_height {1.0f}, m_projection {1.0f}
		{
			create(left, right, bottom, top);
		}

		void Camera::create(const float left, const float right, const float bottom, const float top) noexcept
		{
			if (right > left)
			{
				m_width = right;
			}
			else
			{
				m_width = left;
			}

			if (bottom > top)
			{
				m_height = bottom;
			}
			else
			{
				m_height = top;
			}

			m_projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		}

		void Camera::on_key_down(const events::KeyDown& e) noexcept
		{
			switch (e.m_keycode)
			{
				case input::Keys::W:
					m_move_up = true;
					break;

				case input::Keys::S:
					m_move_down = true;
					break;

				case input::Keys::A:
					m_move_left = true;
					break;

				case input::Keys::D:
					m_move_right = true;
					break;
			}
		}

		void Camera::on_key_up(const events::KeyUp& e) noexcept
		{
			switch (e.m_keycode)
			{
				case input::Keys::W:
					m_move_up = false;
					break;

				case input::Keys::S:
					m_move_down = false;
					break;

				case input::Keys::A:
					m_move_left = false;
					break;

				case input::Keys::D:
					m_move_right = false;
					break;
			}
		}

		void Camera::on_event(const events::MouseWheel& e) noexcept
		{
			if (e.m_y_offset < 0)
			{
				m_scale -= 0.1;
			}
			else
			{
				m_scale += 0.1;
			}

			zoom(m_scale);
		}

		void Camera::on_event(const events::WindowResized& e) noexcept
		{
			create(0.0f, e.m_width, e.m_height, 0.0f);
		}

		void Camera::update(const double ts) noexcept
		{
			if (m_move_up)
			{
				move(0.0f, ts * m_speed);
			}

			if (m_move_down)
			{
				move(0.0f, (ts * m_speed) * -1.0f);
			}

			if (m_move_left)
			{
				move(ts * m_speed, 0.0f);
			}

			if (m_move_right)
			{
				move((ts * m_speed) * -1.0f, 0.0f);
			}
		}

		void Camera::move(const float x, const float y) noexcept
		{
			m_translation = glm::translate(m_translation, {x, y, 0.0f});
			m_pos.x += x;
			m_pos.y += y;

			m_dirty = true;
		}

		void Camera::zoom(const float scale) noexcept
		{
			m_scaling = glm::scale(m_identity_matrix, {scale, scale, 1.0f});
			m_scale   = scale;

			m_dirty = true;
		}

		void Camera::recalculate() noexcept
		{
			if (m_dirty)
			{
				m_model = m_translation * m_scaling;
				m_dirty = false;
			}
		}

		void Camera::set_pos(const float x, const float y) noexcept
		{
			m_translation = glm::translate(m_identity_matrix, {x, y, 0.0f});

			m_pos.x = x;
			m_pos.y = y;

			m_dirty = true;
		}

		void Camera::set_speed(const float speed) noexcept
		{
			m_speed = speed;
		}

		const float Camera::get_speed() const noexcept
		{
			return m_speed;
		}

		const float Camera::get_width() const noexcept
		{
			return m_width;
		}

		const float Camera::get_height() const noexcept
		{
			return m_height;
		}

		const bool Camera::is_dirty() const noexcept
		{
			return m_dirty;
		}

		const glm::mat4& Camera::get_transform() noexcept
		{
			recalculate();
			return m_model;
		}

		const float Camera::get_scale() const noexcept
		{
			return m_scale;
		}

		const glm::vec2& Camera::get_pos() const noexcept
		{
			return m_pos;
		}

		const glm::mat4& Camera::get_proj() noexcept
		{
			return m_projection;
		}

		nlohmann::json Camera::serialize()
		{
			nlohmann::json json = "{}"_json;
			json["x"]           = m_pos.x;
			json["y"]           = m_pos.y;
			json["zoom"]        = m_scale;
			json["speed"]       = m_speed;

			return json;
		}

		void Camera::deserialize(const nlohmann::json& json)
		{
			set_pos(json.at("x"), json.at("y"));
			zoom(json.at("zoom"));
			set_speed(json.at("speed"));

			recalculate();
		}
	} // namespace graphics
} // namespace galaxy