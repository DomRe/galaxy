///
/// Object.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_MAP_TYPES_OBJECT_HPP_
#define GALAXY_MAP_TYPES_OBJECT_HPP_

#include <robin_hood.h>

#include "galaxy/map/types/Text.hpp"
#include "galaxy/map/types/Point.hpp"
#include "galaxy/map/types/Property.hpp"

namespace galaxy
{
	namespace map
	{
		///
		/// Object representation in tiled.
		///
		class Object final
		{
		public:
			///
			/// Default constructor.
			///
			Object();

			///
			/// \brief Parse constructor.
			///
			/// Can throw exceptions.
			///
			/// \param json JSON structure/array containing object.
			///
			explicit Object(const nlohmann::json& json);

			///
			/// Destructor.
			///
			~Object();

			///
			/// \brief Parse object level json.
			///
			/// Can throw exceptions.
			///
			/// \param json JSON structure/array containing object.
			///
			void parse(const nlohmann::json& json);

			///
			/// Get ellipse flag.
			///
			/// \return True if ellipse shaped.
			///
			[[nodiscard]] const bool is_ellipse() const;

			///
			/// Get gid.
			///
			/// \return Gid as const int.
			///
			[[nodiscard]] const int get_gid() const;

			///
			/// Get name.
			///
			/// \return Name as std::string.
			///
			[[nodiscard]] std::string get_name() const;

			///
			/// Get point flag.
			///
			/// \return True if object is point shaped.
			///
			[[nodiscard]] const bool is_point() const;

			///
			/// Gets points.
			///
			/// \return Points as std::vector array.
			///
			[[nodiscard]] const auto& get_points() const;

			///
			/// Retrieve property.
			/// You will need to provide the type when retrieving.
			///
			/// \param name Name of the property to retrieve.
			///
			/// \return Property cast as type.
			///
			template<tiled_property Type>
			[[nodiscard]] const Type get_property(std::string_view name);

			///
			/// Get rotation of object.
			///
			/// \return Double - angle in degrees clockwise.
			///
			[[nodiscard]] const double get_rotation() const;

			///
			/// Get template reference.
			///
			/// \return String reference to a template file, in case object is a template instance.
			///
			[[nodiscard]] std::string get_template() const;

			///
			/// Get text object (if object is text based).
			///
			/// \return Const reference to a text object.
			///
			[[nodiscard]] const Text& get_text() const;

			///
			/// Get type string.
			///
			/// \return String assigned to type field in editor.
			///
			[[nodiscard]] std::string get_type() const;

			///
			/// Get visibility.
			///
			/// \return True if object is visible.
			///
			[[nodiscard]] const bool is_visible() const;

			///
			/// Get width of object.
			///
			/// \return Width in pixels as double.
			///
			[[nodiscard]] const double get_width() const;

			///
			/// Get width of object.
			///
			/// \return Width in pixels as double.
			///
			[[nodiscard]] const double get_x() const;

			///
			/// Get width of object.
			///
			/// \return Width in pixels as double.
			///
			[[nodiscard]] const double get_y() const;

		private:
			///
			/// Used to mark an object as an ellipse.
			///
			bool m_ellipse;

			///
			/// Global tile ID, only if object represents a tile.
			///
			int m_gid;

			///
			/// Height in pixels.
			///
			double m_height;

			///
			/// Incremental id, unique across all objects.
			///
			int m_id;

			///
			/// String assigned to name field in editor.
			///
			std::string m_name;

			///
			/// Used to mark an object as a point.
			///
			bool m_point;

			///
			/// Array of Points, in case the object is a polygon/polyline
			///
			std::vector<Point> m_points;

			///
			/// Map of Properties.
			///
			robin_hood::unordered_map<std::string, Property> m_properties;

			///
			/// Angle in degrees clockwise.
			///
			double m_rotation;

			///
			/// Reference to a template file, in case object is a template instance.
			///
			std::string m_template;

			///
			/// Only used for text objects.
			///
			Text m_text;

			///
			/// String assigned to type field in editor.
			///
			std::string m_type;

			///
			/// Whether object is shown.
			///
			bool m_visible;

			///
			/// Width in pixels.
			///
			double m_width;

			///
			/// X coordinate in pixels.
			///
			double m_x;

			///
			/// Y coordinate in pixels.
			///
			double m_y;
		};

		template<tiled_property Type>
		inline const Type Object::get_property(std::string_view name)
		{
			const auto str = static_cast<std::string>(name);
			return m_properties[str].get<Type>();
		}
	} // namespace map
} // namespace galaxy

#endif