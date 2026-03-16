#include "../RendererShared.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace engine::internal;

namespace {
    std::string resolvePath(const std::string& relName) {
        char buf[4096];

#ifdef _WIN32
        GetModuleFileNameA(NULL, buf, sizeof(buf));
#else
        ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        if (len == -1)
            throw std::runtime_error("ShaderLoader: /proc/self/exe unreadable");
        buf[len] = '\0';
#endif

        std::filesystem::path exeDir = std::filesystem::path(buf).parent_path();
        return (exeDir / ".." / "src" / "assets" / "shaders" / relName).string();
    }

	std::string readFile(const std::string& path) {
		std::ifstream file(path);
		if (!file.is_open())
			throw std::runtime_error("ShaderLoader: cannot open: " + path);
		std::ostringstream ss;
		ss << file.rdbuf();
		return ss.str();
	}

	GLuint compileShader(GLenum type, const std::string& source) {
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
				" shader compile error:\n" + log
			);
		}
		return shader;
	}
}

GLuint RendererShared::loadShader(const std::string& vertRelPath, const std::string& fragRelPath) {
	GLuint vert = compileShader(GL_VERTEX_SHADER,   readFile(resolvePath(vertRelPath)));
	GLuint frag = compileShader(GL_FRAGMENT_SHADER, readFile(resolvePath(fragRelPath)));

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
		throw std::runtime_error("Shader link error:\n" + std::string(log));
	}

	return program;
}
