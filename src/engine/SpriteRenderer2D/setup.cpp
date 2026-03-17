#include "../SpriteRenderer2D.hpp"

void SpriteRenderer2D::setup() {

	shaderProgram = Renderer::loadShader("tile.vert", "tile.frag");

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &quadVBO);
	glGenBuffers(1, &quadEBO);
	glGenBuffers(1, &instanceVBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Renderer::q_vertices_uv), Renderer::q_vertices_uv, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Renderer::q_indices), Renderer::q_indices, GL_STATIC_DRAW);

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

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(instanceData), instanceData, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Renderer::QuadVertexUV), (void*)offsetof(Renderer::QuadVertexUV, pos));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Renderer::QuadVertexUV), (void*)offsetof(Renderer::QuadVertexUV, uv));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, position));
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribIPointer(3, 1, GL_UNSIGNED_INT, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, layer));
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(InstanceVertex), (void*)offsetof(InstanceVertex, color));
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
