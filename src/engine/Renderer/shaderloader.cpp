#include "../Renderer.hpp"
#include "../ResourceManager.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>

std::string readFile(const std::string& path) {
	std::ifstream file(path);
	if (!file.is_open())
		throw std::runtime_error("Nem sikerült megnyitni a shadert: " + path);
	std::ostringstream ss;
	ss << file.rdbuf();
	return ss.str();
}

GLuint compileShader(GLenum type, const std::filesystem::path& source) {
	GLuint shader = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(shader, 1, &src, nullptr);
	glCompileShader(shader);

	GLint ok;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (!ok) {
		char log[512];
		glGetShaderInfoLog(shader, 512, nullptr, log);
		glDeleteShader(shader);
		throw std::runtime_error(
		std::string(type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") +
			" shader compile hiba:\n" + log
		);
	}
	return shader;
}

GLuint Renderer::loadShader(const std::string& vertRelPath, const std::string& fragRelPath) {
	GLuint vert = compileShader(GL_VERTEX_SHADER,   readFile(ResourceManager::getAssetsFolder() / vertRelPath));
	GLuint frag = compileShader(GL_FRAGMENT_SHADER, readFile(ResourceManager::getAssetsFolder() / fragRelPath));

	GLuint program = glCreateProgram();
	glAttachShader(program, vert);
	glAttachShader(program, frag);
	glLinkProgram(program);

	glDeleteShader(vert);
	glDeleteShader(frag);

	GLint ok;
	glGetProgramiv(program, GL_LINK_STATUS, &ok);
	if (!ok) {
		char log[512];
		glGetProgramInfoLog(program, 512, nullptr, log);
		glDeleteProgram(program);
		throw std::runtime_error("Shader link hiba:\n" + std::string(log));
	}

	return program;
}


