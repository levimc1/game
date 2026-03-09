#include <print>

using namespace engine;

int main() {

  println("Hello, {}", "World!");

	EngineContext e = EngineContext::create();

	TestRenderer renderer{
		.schema{
			.color = {0.0, 0.5, 1.0},
		}
	}

	e.regSystems(renderer);

	e.targetFPS{60.0f};

	Közd össze több rendszerrel
	//renderer.connection({.vertexData{other.id}})

	return e.run({
		.frame{[&]() {
			renderer.draw();
		}},
	})
}