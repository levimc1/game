#pragma once

#include <engine/state.hpp>
#include "SpriteRenderer2DState.hpp"
#include "RendererShared.hpp"

namespace engine {

	struct SpriteRenderer2D : internal::System {

		SpriteRenderer2D() : internal::System(internal::SystemDesc("SpriteRenderer2D", internal::SystemDesc::Setup)) {}

		void makeState() override {
			id = internal::EngineState::makeState<SpriteRenderer2DState>();
			internal::EngineState::regShared<internal::RendererShared>();
		}

		void setup() override;
    	
		inline bool condition() {return internal::EngineState::getShared<internal::RendererShared>().condition();}

		void draw();

	};

}