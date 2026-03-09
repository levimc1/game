#pragma once

namespace engine {

  struct EngineContext {
	// Lifetime, adat (és bindolás)

		inline static EngineContext create() {
			// De most nem kell
			return EngineContext{};
		}
		// Initel globálisan ha kell, majd létrehozza a contextust és visszaadja

		
  };
}