///
/// Scene3D.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_SCENES_SCENE3D_HPP_
#define GALAXY_SCENES_SCENE3D_HPP_

#include "galaxy/scenes/Scene.hpp"

namespace galaxy
{
	namespace scene
	{
		///
		/// 3D scene implementation.
		///
		class Scene3D final : public Scene
		{
		public:
			///
			/// Argument Constructor.
			///
			/// \param name Name of the Scene3D.
			///
			Scene3D(std::string_view name) noexcept;

			///
			/// Destructor.
			///
			virtual ~Scene3D() noexcept;

			///
			/// On push of Scene3D to stack.
			///
			void on_push() override;

			///
			/// On pop of Scene3D off stack.
			///
			void on_pop() override;

			///
			/// Process events.
			///
			void events() override;

			///
			/// Process update (fixed timestep) logic.
			///
			/// \param dt Delta-Time from fixed timestep gameloop.
			///
			void update(const double dt) override;

			///
			/// Code to be called before rendering. Outside of any glBegin, window.begin(), etc...
			///
			void pre_render() override;

			///
			/// Render to screen.
			///
			void render() override;

			///
			/// Serializes object.
			///
			/// \return JSON object containing data to write out.
			///
			[[nodiscard]] nlohmann::json serialize() override;

			///
			/// Deserializes from object.
			///
			/// \param json Json object to retrieve data from.
			///
			void deserialize(const nlohmann::json& json) override;

		private:
			///
			/// Deleted default constructor.
			///
			Scene3D() = delete;
		};
	} // namespace scene
} // namespace galaxy

#endif