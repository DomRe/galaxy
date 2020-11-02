///
/// GUILayer.cpp
/// sandbox_tests
///
/// Refer to LICENSE.txt for more details.
///

#include <qs/core/Renderer.hpp>

#include <galaxy/core/ServiceLocator.hpp>
#include <galaxy/fs/FileSystem.hpp>
#include <galaxy/res/FontBook.hpp>
#include <galaxy/res/ShaderBook.hpp>
#include <qs/core/Window.hpp>

#include <galaxy/ui/widgets/Image.hpp>
#include <galaxy/ui/widgets/Label.hpp>
#include <galaxy/ui/widgets/Button.hpp>

#include <protostar/events/MouseMovedEvent.hpp>

#include "GUILayer.hpp"

// clang-format off
#define WHITE {255, 255, 255, 255}
#define BLACK {0, 0, 0, 255}
#define RED {255, 0, 0, 255}
// clang-format on

///
/// Core namespace.
///
namespace sb
{
	GUILayer::GUILayer()
	{
		set_name("gui_layer");

		auto demo_tex = galaxy::FileSystem::s_root + galaxy::FileSystem::s_textures + "demo_nineslice.png";

		auto button_default = galaxy::FileSystem::s_root + galaxy::FileSystem::s_textures + "button_default.png";
		auto button_pressed = galaxy::FileSystem::s_root + galaxy::FileSystem::s_textures + "button_pressed.png";
		auto button_hover   = galaxy::FileSystem::s_root + galaxy::FileSystem::s_textures + "button_hover.png";

		auto demo_font  = galaxy::FileSystem::s_root + galaxy::FileSystem::s_fonts + "public.ttf";
		auto rtt_shader = SL_HANDLE.shaderbook()->get("render_to_texture");

		m_theme.m_fonts    = SL_HANDLE.fontbook();
		m_theme.m_shaders  = SL_HANDLE.shaderbook();
		m_theme.m_renderer = SL_HANDLE.renderer();
		m_theme.m_window   = SL_HANDLE.window();
		m_theme.m_font_col = RED;

		m_theme.m_fonts->create("public16", demo_font, 16);
		m_theme.m_atlas.add(demo_tex);
		m_theme.m_atlas.add(button_default);
		m_theme.m_atlas.add(button_pressed);
		m_theme.m_atlas.add(button_hover);

		rtt_shader->bind();
		m_theme.m_atlas.create(*SL_HANDLE.renderer(), *rtt_shader);

		m_gui.set_theme(&m_theme);
		m_gui.construct(*SL_HANDLE.pool());

		auto* image = m_gui.create_widget<galaxy::widget::Image>();
		image->create_from_atlas("demo_nineslice");

		auto* tooltip = m_gui.create_tooltip_for_widget(image);
		tooltip->create(demo_tex, "Demo Test", "public16");

		m_gui.add_event_to_widget<pr::MouseMovedEvent>(image);

		auto* label = m_gui.create_widget<galaxy::widget::Label>();
		label->create("Label Demo", "public16");
		label->set_pos(300, 300);

		auto* button = m_gui.create_widget<galaxy::widget::Button>();
		button->create_from_atlas({"button_default", "button_pressed", "button_hover"});
		button->set_pos(250, 250);
		button->set_callback([&]() {
			PL_LOG(PL_INFO, "Button Pressed.");
		});

		m_gui.add_event_to_widget<pr::MousePressedEvent>(button);
		m_gui.add_event_to_widget<pr::MouseReleasedEvent>(button);
	}

	GUILayer::~GUILayer()
	{
	}

	void GUILayer::events()
	{
		auto pos = SL_HANDLE.window()->get_cursor_pos();
		m_gui.trigger<pr::MouseMovedEvent>(pos.x, pos.y);

		if (glfwGetMouseButton(SL_HANDLE.window()->gl_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			m_gui.trigger<pr::MousePressedEvent>(pos.x, pos.y, GLFW_MOUSE_BUTTON_LEFT);
		}

		if (glfwGetMouseButton(SL_HANDLE.window()->gl_window(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
		{
			m_gui.trigger<pr::MouseReleasedEvent>(pos.x, pos.y, GLFW_MOUSE_BUTTON_LEFT);
		}
	}

	void GUILayer::update(const double dt)
	{
		m_gui.update();
	}

	void GUILayer::render(qs::Camera& camera)
	{
		m_gui.render(camera);
	}
} // namespace sb