#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Particle {
    glm::vec2 pos;
    glm::vec2 vel;
};

GLuint compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    return shader;
}

int main() {
    if (!glfwInit())
        return -1;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Particle Simulator", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return -1;
    }

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<Particle> particles(100);
    for (auto &p : particles) {
        p.pos = glm::vec2((float)std::rand() / RAND_MAX * 2 - 1,
                          (float)std::rand() / RAND_MAX * 2 - 1);
        p.vel = glm::vec2(((float)std::rand() / RAND_MAX - 0.5f) * 0.01f,
                          ((float)std::rand() / RAND_MAX - 0.5f) * 0.01f);
    }

    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, particles.size() * sizeof(glm::vec2), nullptr, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
    glEnableVertexAttribArray(0);

    const char* vs_src = "#version 330 core\n"
        "layout(location = 0) in vec2 aPos;\n"
        "void main() {\n"
        "    gl_PointSize = 4.0;\n"
        "    gl_Position = vec4(aPos, 0.0, 1.0);\n"
        "}";

    const char* fs_src = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "    FragColor = vec4(1.0, 0.5, 0.2, 1.0);\n"
        "}";

    GLuint vs = compileShader(GL_VERTEX_SHADER, vs_src);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, fs_src);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);

    glUseProgram(program);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto &p : particles) {
            p.pos += p.vel;
            if (p.pos.x > 1.0f || p.pos.x < -1.0f) p.vel.x = -p.vel.x;
            if (p.pos.y > 1.0f || p.pos.y < -1.0f) p.vel.y = -p.vel.y;
        }
        glBufferSubData(GL_ARRAY_BUFFER, 0, particles.size() * sizeof(glm::vec2), &particles[0].pos);
        glDrawArrays(GL_POINTS, 0, particles.size());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteProgram(program);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

