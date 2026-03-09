#pragma once

#include <extern/glm/glm.hpp>
#include "TestRendererState.hpp"

namespace engine {

	struct TestRenderer {

		internal::TestRendererState* state;

		struct TestRendererSchema {
			glm::vec3 color;
		} schema;

		// Majd konnekció
		// De erre nem kell

		void draw();
		// schema és konnekció alapján olvas state-et
	};
}