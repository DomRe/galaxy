///
/// TileOffset.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_MAP_TILE_TILEOFFSET_HPP_
#define GALAXY_MAP_TILE_TILEOFFSET_HPP_

#include <nlohmann/json_fwd.hpp>

namespace galaxy
{
	namespace map
	{
		///
		/// This element is used to specify an offset in pixels, to be applied when drawing a tile from the related tileset. When not present, no offset is applied.
		///
		class TileOffset final
		{
		public:
			///
			/// Default constructor.
			///
			TileOffset();

			///
			/// \brief Parse constructor.
			///
			/// Can throw exceptions.
			///
			/// \param json JSON structure/array containing tileoffset json.
			///
			explicit TileOffset(const nlohmann::json& json);

			///
			/// Default destructor.
			///
			~TileOffset() = default;

			///
			/// \brief Parses json structure to member values; etc.
			///
			/// Can throws exceptions.
			///
			/// \param json JSON structure containing tileoffset json.
			///
			void parse(const nlohmann::json& json);

			///
			/// Get horizontal offset.
			///
			/// \return Const int. In pixels.
			///
			[[nodiscard]] const int get_x() const;

			///
			/// Get vertical offset.
			///
			/// \return Const int. In pixels, positive is down.
			///
			[[nodiscard]] const int get_y() const;

		private:
			///
			/// Horizontal offset in pixels.
			///
			int m_x;

			///
			/// Vertical offset in pixels (positive is down).
			///
			int m_y;
		};
	} // namespace map
} // namespace galaxy

#endif