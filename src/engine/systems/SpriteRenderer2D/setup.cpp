#include "../SpriteRenderer2D.hpp"
#include "../RendererShared.hpp"
#include <extern/glm/glm.hpp>
#include <cstddef>

using namespace engine;

using Shared = internal::RendererShared;

void SpriteRenderer2D::setup() {

	auto& state = internal::EngineState::getState<SpriteRenderer2DState>(id);

	state.shaderProgram = Shared::loadShader("tile.vert", "tile.frag");

	glGenVertexArrays(1, &state.VAO);
	glGenBuffers(1, &state.quadVBO);
	glGenBuffers(1, &state.quadEBO);
	glGenBuffers(1, &state.instanceVBO);

	glBindVertexArray(state.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, state.quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Shared::q_vertices_uv), Shared::q_vertices_uv, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, state.quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Shared::q_indices), Shared::q_indices, GL_STATIC_DRAW);

	struct InstanceVertex {
    glm::vec2 position;
		glm::uint32 layer;
    glm::vec3 color;
	};

	InstanceVertex instanceData[] = {
	  { {0.0f, 0.0f		}, 0, {1.0f, 0.0f, 0.0f} },
 	  { {0.5f, 0.5f		}, 1, {0.0f, 1.0f, 0.0f} },
  	{ {0.0f, 0.8427f}, 0, {0.0f, 0.0f, 1.0f} },
	};

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(instanceData), instanceData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, state.quadVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Shared::QuadVertexUV), (void*)offsetof(Shared::QuadVertexUV, pos));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, state.quadVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Shared::QuadVertexUV), (void*)offsetof(Shared::QuadVertexUV, uv));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, position));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, layer));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, state.instanceVBO);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, color));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	
}