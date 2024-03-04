//
// This file is a part of the Open Source Design456App
// MIT License
//
// Copyright (c) 2024
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//  Original Author : Gabriel de Quadros  https://github.com/gligneul
//  Modified to use with this project by :
//  Author :Mariwan Jalal    mariwan.jalal@gmail.com
//

#ifndef FR_LIGHT_H
#define FR_LIGHT_H

#include<frtk.h>
#include<fr_core.h>

#include <fr_node.h>
namespace FR {
	class FRTK_API Light : public Node {
	public:
		/**
		 * Default constructor
		 */
		Light(glm::vec4 lightcolor = glm::vec4(1, 1, 1, 1));
		// Move Constructor
		Light(Light&& other) noexcept
			: Node(std::move(other)), // Move the base class part
			lightColor_(std::move(other.lightColor_)),
			position_(std::move(other.position_)),
			ambient_(std::move(other.ambient_)),
			diffuse_(std::move(other.diffuse_)),
			specular_(std::move(other.specular_)),
			attenuation_(std::move(other.attenuation_)),
			spot_enabled_(other.spot_enabled_),
			spot_direction_(std::move(other.spot_direction_)),
			spot_cutoff_Ang(other.spot_cutoff_Ang),
			spot_exponent_(other.spot_exponent_),
			sm_enable_(other.sm_enable_),
			sm_direction_(std::move(other.sm_direction_)),
			sm_up_(std::move(other.sm_up_)),
			sm_projection_(std::move(other.sm_projection_)),
			sm_framebuffer_(other.sm_framebuffer_),
			sm_renderbuffer_(other.sm_renderbuffer_),
			shadowMapTexture_(other.shadowMapTexture_) {
			// Optionally, reset the moved-from object's state if needed.
			other.sm_framebuffer_ = 0;
			other.sm_renderbuffer_ = 0;
			other.shadowMapTexture_ = 0;
		}
		Light(const Light& other)
			: Node(other),
			lightColor_(other.lightColor_),
			position_(other.position_),
			ambient_(other.ambient_),
			diffuse_(other.diffuse_),
			specular_(other.specular_),
			attenuation_(other.attenuation_),
			spot_enabled_(other.spot_enabled_),
			spot_direction_(other.spot_direction_),
			spot_cutoff_Ang(other.spot_cutoff_Ang),
			spot_exponent_(other.spot_exponent_),
			sm_enable_(other.sm_enable_),
			sm_direction_(other.sm_direction_),
			sm_up_(other.sm_up_),
			sm_projection_(other.sm_projection_),
			sm_framebuffer_(other.sm_framebuffer_),
			sm_renderbuffer_(other.sm_renderbuffer_),
			shadowMapTexture_(other.shadowMapTexture_) {
			// Optional: Copy any additional resources or reset state if needed
		}
		~Light() = default; // Destructor

		Light& operator=(Light&& other) noexcept {
			if (this != &other) {
				Node::operator=(std::move(other)); // Move the base class part
				lightColor_ = std::move(other.lightColor_);
				position_ = std::move(other.position_);
				// ... move other members ...
				// Reset the moved-from object's state if needed.
				other.sm_framebuffer_ = 0;
				other.sm_renderbuffer_ = 0;
				other.shadowMapTexture_ = 0;
			}
			return *this;
		}

		/**
		* Light color
		*/
		void SetLightColor(glm::vec4 lightColor);

		/**
		* Sets the light position
		*/
		void SetPosition(glm::vec4 pos);

		/**
		 * Sets the light position
		 * Default = 0, 0, 0
		 */
		void SetPosition(float x, float y, float z, float w = 1.0f);

		/**
		 * Sets the ambient component
		 * Default = 0.2, 0.2, 0.2, 1.0
		 */
		void SetAmbient(float r, float g, float b, float a = 1.0f);

		/**
		 * Sets the diffuse component
		 * Default = 0.4, 0.4, 0.4, 1.0
		 */
		void SetDiffuse(float r, float g, float b, float a = 1.0f);

		/**
		 * Sets the specular component
		 * Default = 0.4, 0.4, 0.4, 1.0
		 */
		void SetSpecular(float r, float g, float b, float a = 1.0f);

		/**
		 * Sets the attenuation: 1 / (c + l*d + q*d^2)
		 * Default = (1, 0, 0)
		 */
		void SetAttenuation(float c, float l, float q);

		/**
		* Setup spot
		*/
		void SetupSpot(float x, float y, float z, float cutoffAngle, float exponent);

		/**
		 * Enables the shadow map
		 */
		void EnableShadowMap(const glm::vec3& center, const glm::vec3& up, const glm::mat4& projection);

		/**
		 * Sets the lights
		 * Returns the light info by reference
		 */
		void SetupLight(const glm::mat4& modelview, std::vector<LightInfo>& lights) override;

	public:

		glm::vec4 getPosition();
		glm::vec4 gtAmbient();
		glm::vec4 getDiffuse();
		glm::vec4 getSpecular();
		glm::vec3 getAttenuation();

	private:
		// Constants
		const int kShadowmapWidth = 1024;
		const int kShadowmapHeight = kShadowmapWidth;

		// Attributes
		glm::vec4 lightColor_;
		glm::vec4 position_;
		glm::vec4 ambient_;
		glm::vec4 diffuse_;
		glm::vec4 specular_;
		glm::vec3 attenuation_;
		bool spot_enabled_;
		glm::vec4 spot_direction_;
		float spot_cutoff_Ang;
		float spot_exponent_;

		bool sm_enable_;
		glm::vec3 sm_direction_;
		glm::vec3 sm_up_;
		glm::mat4 sm_projection_;
		unsigned int sm_framebuffer_;
		unsigned int sm_renderbuffer_;
		unsigned int shadowMapTexture_;
	};
}
#endif
