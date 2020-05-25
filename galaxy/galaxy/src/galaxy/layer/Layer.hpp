///
/// Layer.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_LAYER_HPP_
#define GALAXY_LAYER_HPP_

#include <string>

#include <protostar/async/ProtectedArithmetic.hpp>

///
/// Core namespace.
///
namespace galaxy
{
	///
	/// Represents a "layer" in the engine, encapsulating things like events and rendering.
	///
	class Layer
	{
	public:
		///
		/// Default virtual destructor.
		///
		virtual ~Layer() noexcept = default;

		///
		/// Code to call when layer is pushed to top.
		///
		virtual void onPush() noexcept = 0;

		///
		/// Copde to call when layer is popped from stack.
		///
		virtual void onPop() noexcept = 0;

		///
		/// Process layer events.
		///
		virtual void events() noexcept = 0;

		///
		/// Process update (fixed timestep) logic.
		///
		/// \param deltaTime Delta-Time from fixed timestep gameloop.
		///
		virtual void update(protostar::ProtectedDouble* deltaTime) noexcept = 0;

		///
		/// \brief Render layer.
		///
		/// Does NOT allow std::exceptions!
		///
		virtual void render() noexcept = 0;

		///
		/// Set layer name.
		///
		/// \param name Name in std::string format.
		///
		virtual void setName(const std::string& name) noexcept final;

		///
		/// Get layer name.
		///
		/// \return Const std::string.
		///
		virtual const std::string& getName() noexcept final;

	protected:
		///
		/// Default constructor.
		///
		Layer() noexcept;

		///
		/// Argument constructor.
		///
		/// \param name Gives the layer a name.
		///
		explicit Layer(const std::string& name) noexcept;

	protected:
		///
		/// Layer name. Useful to have.
		///
		std::string m_name;
	};
}

#endif