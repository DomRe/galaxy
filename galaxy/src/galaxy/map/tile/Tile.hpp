///
/// Tile.hpp
/// starmap
///
/// Refer to LICENSE.txt for more details.
///

#ifndef STARMAP_TILE_HPP_
#define STARMAP_TILE_HPP_

#include <optional>

#include "starmap/types/Frame.hpp"
#include "starmap/layer/ObjectLayer.hpp"

///
/// Core namespace.
///
namespace starmap
{
	///
	/// A tile on a tileset.
	///
	class Tile final
	{
	public:
		///
		/// Constructor.
		///
		Tile();

		///
		/// \brief Parse constructor.
		///
		/// Can throw exceptions.
		///
		/// \param json JSON structure/array containing tile json.
		///
		explicit Tile(const nlohmann::json& json);

		///
		/// Destructor.
		///
		~Tile();

		///
		/// \brief Parses json structure to member values; etc.
		///
		/// Can throws exceptions.
		///
		/// \param json JSON structure containing tile json.
		///
		void parse(const nlohmann::json& json);

		///
		/// Get animation frames.
		///
		/// \return Std::vector array.
		///
		[[nodiscard]] const auto& get_animations() const;

		///
		/// Get local tile id.
		///
		/// \return Const int.
		///
		[[nodiscard]] const int get_id() const;

		///
		/// Get image representing the tile.
		///
		/// \return Const std::string reference.
		///
		[[nodiscard]] std::string get_image() const;

		///
		/// Height of the tile.
		///
		/// \return Const int. In pixels.
		///
		[[nodiscard]] const int get_image_height() const;

		///
		/// Width of the tile.
		///
		/// \return Const int. In pixels.
		///
		[[nodiscard]] const int get_image_width() const;

		///
		/// Get the object group of the Tile.
		///
		/// \return Returns a std::optional. Make sure you check for std::nullopt if tile offset is not used!
		///
		[[nodiscard]] const auto& get_object_group() const;

		///
		/// Chance this tile is chosen when competing with others in the editor.
		///
		/// \return Const double. This is a percentage. Will return -1.0 if not used.
		///
		[[nodiscard]] const double get_probability() const;

		///
		/// \brief Retrieve property.
		///
		/// You will need to provide the type when retrieving.
		///
		/// \param name Name of the property to retrieve.
		///
		/// \return Property cast as type.
		///
		template<tiled_property Type>
		[[nodiscard]] const Type get_property(std::string_view name);

		///
		/// Get index of terrain for each corner of tile.
		///
		/// \return std::vector int array.
		///
		[[nodiscard]] const auto& get_terrain_indices() const;

		///
		/// Get the type of tile.
		///
		/// \return Const std::string reference.
		///
		[[nodiscard]] std::string get_type() const;

	private:
		///
		/// Array of Frames.
		///
		std::vector<starmap::Frame> m_animation;

		///
		/// Local ID of the tile.
		///
		int m_id;

		///
		/// Image representing this tile (optional).
		///
		std::string m_image;

		///
		/// Height of the tile image in pixels.
		///
		int m_image_height;

		///
		/// Width of the tile image in pixels.
		///
		int m_image_width;

		///
		/// Layer with type objectgroup, when collision shapes are specified (optional).
		///
		std::optional<starmap::ObjectLayer> m_object_group;

		///
		/// Percentage chance this tile is chosen when competing with others in the editor (optional).
		///
		double m_probability;

		///
		/// Map of Properties.
		///
		robin_hood::unordered_map<std::string, starmap::Property> m_properties;

		///
		/// Index of terrain for each corner of tile (optional).
		///
		std::vector<int> m_terrain_indices;

		///
		/// The type of the tile (optional).
		///
		std::string m_type;
	};

	template<tiled_property Type>
	inline const Type Tile::get_property(std::string_view name)
	{
		const auto str = static_cast<std::string>(name);
		return m_properties[str].get<Type>();
	}
} // namespace starmap

#endif