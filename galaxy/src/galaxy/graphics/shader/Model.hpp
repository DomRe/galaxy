///
/// Model.hpp
/// galaxy
///
/// Refer to LICENSE.txt for more details.
///

#ifndef GALAXY_GRAPHICS_SHADER_MODEL_HPP_
#define GALAXY_GRAPHICS_SHADER_MODEL_HPP_

#include <string>

namespace galaxy
{
	namespace shaders
	{
		///
		/// Model vertex shader.
		///
		inline const std::string model_vert = R"(
			#version 450 core
			layout(location = 0) in vec3 l_pos;
			layout(location = 1) in vec3 l_normals;
			layout(location = 2) in vec2 l_texels;

			out vec2 io_texels;

			uniform mat4 u_transform;
			uniform mat4 u_cameraView;
			uniform mat4 u_cameraProj;

			void main()
			{
				gl_Position = u_cameraProj * u_cameraView * u_transform * vec4(l_pos, 1.0);
				io_texels = l_texels;
			}
		)";

		///
		/// Model fragment shader.
		///
		inline const std::string model_frag = R"(
			#version 450 core

			in vec2 io_texels;
			out vec4 io_frag_colour;

			uniform sampler2D tex_DIFFUSE1;
			uniform sampler2D tex_SPECULAR1;
			uniform sampler2D tex_NORMAL1;

			void main()
			{
				io_frag_colour = texture(tex_DIFFUSE1, io_texels);
			}
		)";
	} // namespace shaders
} // namespace galaxy

#endif