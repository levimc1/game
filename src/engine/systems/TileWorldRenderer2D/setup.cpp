#include "../TileWorldRenderer2D.hpp"
#include "../RendererShared.hpp"
#include <extern/glm/glm.hpp>
#include <cstddef>

using namespace engine;

void TileWorldRenderer2D::setup() {

	auto& state = internal::getState<TileWorldRenderer2DState>();

	state.shaderProgram = Shared::loadShader("tile.vert", "tile.frag");

	glGenVertexArrays(1, &state.VAO);
	glGenBuffers(1, &state.quadVBO);
	glGenBuffers(1, &state.quadEBO);
	glGenBuffers(1, &state.instanceVBO);

	glBindVertexArray(state.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, state.quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Shared::vertices), Shared::vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Shared::indices), Shared::indices, GL_STATIC_DRAW);

	struct InstanceVertex {
    glm::vec2 position;
    glm::vec3 color;
	};

	InstanceVertex instanceData[] = {
    { {0.0f, 0.0f},   {1.0f, 0.0f, 0.0f} },
    { {0.5f, 0.5f},   {0.0f, 1.0f, 0.0f} },
    { {0.0f, 0.8427f},{0.0f, 0.0f, 1.0f} },
	};

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceVertex), InstanceVertex, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, state.quadVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), offsetof(InstanceVertex, position));
	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), offsetof(InstanceVertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}