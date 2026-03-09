#pragma once

// Circular dependecy elkerülésére. 

#include <variant>

#include "systems/TestRendererState.hpp"

// Összes state típus 
using State = std::variant<std::monostate, engine::internal::TestRendererState>;
