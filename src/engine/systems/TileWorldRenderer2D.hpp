#pragma once

#include <engine/state.hpp>
#include "TileWorldRenderer2DState.hpp"
#include "RendererShared.hpp"

namespace engine {

	struct TileWorldRenderer2D : internal::System {

		TileWorldRenderer2D() : internal::System(internal::SystemDesc("TileWorldRenderer2D", SystemDesc::Setup)) {}

		void makeSate override {
			id = internal::EngineState::makeState<TileWorldRenderer2DState>();
			internal::EngineState::regShared<internal::RendererShared>();
		}

		void setup() override;

		void draw();

	};

}