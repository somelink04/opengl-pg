#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void fatal(const char* msg) {
    printf("FATAL: %s\n", msg);
}

void onWindowResize(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void onInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

// vertices of the triangle to be rendered
GLfloat vertices[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

const char *vertexShaderSource = 
    "#version 460 core\n"
    "layout (location = 0) in vec3 v;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(v, 1.0);\n"
    "}";

const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}";

int main(void) {
    int retCode = EXIT_SUCCESS;

    if (!glfwInit()) {
        fatal("could not initialize GLFW.");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello, OpenGL!", NULL, NULL);
    if (!window) {
        fatal("could not create GLFW window.");
        retCode = EXIT_FAILURE;
        goto end;
    }

    glfwMakeContextCurrent(window);  
    int loaded_version = gladLoadGL(glfwGetProcAddress);
    if ( loaded_version == 0 ) {
        fatal("Failed to initialize OpenGL context.");
        retCode = EXIT_FAILURE;
        goto end;
    }
    printf(
        "INFO: Loaded OpenGL %i.%i\n", 
        GLAD_VERSION_MAJOR(loaded_version),
        GLAD_VERSION_MINOR(loaded_version));

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    glfwSetFramebufferSizeCallback(window, onWindowResize);

    glfwSetKeyCallback(window, onInput);

    glClearColor(0.4f, 0.2f, 1.0f, 1.0f);

    // Setup shader program
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glUseProgram(shaderProgram);

    // Setup GL objects
    GLuint VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
    
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

end:
    glfwTerminate();
    return retCode;
}
