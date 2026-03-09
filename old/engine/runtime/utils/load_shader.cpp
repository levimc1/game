// engine/common/shader.cpp
#include "utils.hpp"
#include <fstream>
#include <sstream>
#include <print>
#include <filesystem>

#include <extern/glad/glad.h>

// AI KÓD! mert unalmas.
// TODO: error handling-re tudod a e.printErrors! 

namespace engine {

static std::filesystem::path shaderBase() {
    return std::filesystem::canonical("/proc/self/exe").parent_path() / "../src/assets/shaders/";
}

static std::string readFile(const std::string& path) {
    std::filesystem::path full = shaderBase() / path;
    std::ifstream file(full);
    if (!file.is_open()) {
        std::println("[Shader] Nem lehet megnyitni: {}", full.string());
        return "";
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

static GLuint compileShader(GLenum type, const std::string& src, const std::string& path) {
    GLuint shader = glCreateShader(type);
    const char* c = src.c_str();
    glShaderSource(shader, 1, &c, nullptr);
    glCompileShader(shader);

    GLint ok;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::println("[Shader] Hiba: {}\n{}", path, log);
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint utils::loadShader(const std::string& vertPath, const std::string& fragPath) {
    //const std::string base = "../src/assets/shaders/";

    std::string vertSrc = readFile(vertPath);
    std::string fragSrc = readFile(fragPath);
    if (vertSrc.empty() || fragSrc.empty()) return 0;

    GLuint vert = compileShader(GL_VERTEX_SHADER,   vertSrc, vertPath);
    GLuint frag = compileShader(GL_FRAGMENT_SHADER, fragSrc, fragPath);
    if (!vert || !frag) return 0;

    GLuint program = glCreateProgram();
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    glLinkProgram(program);

    GLint ok;
    glGetProgramiv(program, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::println("[Shader] Link hiba:\n{}", log);
        glDeleteProgram(program);
        program = 0;
    }

    glDeleteShader(vert);
    glDeleteShader(frag);
    return program;
}

} // namespace engine
