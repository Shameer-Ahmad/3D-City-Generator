#include <glad/glad.h>  // OpenGL loader
#include <GLFW/glfw3.h> // Window creation
#include <glm/glm.hpp>  // Math library
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

// Shader source code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 FragColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragColor = aColor;
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 FragColor;
out vec4 FragOutput;

void main()
{
    FragOutput = vec4(FragColor, 1.0);
}
)";

// Building structure
struct Building {
    glm::vec3 position;
    float width;
    float depth;
    float height;
    glm::vec3 color;
};

// Function declarations
GLFWwindow* initializeWindow();
unsigned int compileShaders();
void generateCity(std::vector<Building>& buildings, int numBuildings);
void createBuildingBuffers(const std::vector<Building>& buildings, 
                          std::vector<float>& vertices, 
                          std::vector<unsigned int>& indices);
void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

int main() {
    // Initialize window
    GLFWwindow* window = initializeWindow();
    if (!window) return -1;

    // Compile shaders
    unsigned int shaderProgram = compileShaders();
    if (!shaderProgram) return -1;

    // Generate city data
    std::vector<Building> buildings;
    generateCity(buildings, 100); // Generate 100 buildings

    // Create vertex and index data
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    createBuildingBuffers(buildings, vertices, indices);

    // Set up vertex buffer objects and vertex array objects
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Get uniform locations
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Camera setup
    glm::vec3 cameraPos = glm::vec3(0.0f, 50.0f, 150.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // Timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Process input
        processInput(window, cameraPos, cameraFront);

        // Clear the screen
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Activate shader
        glUseProgram(shaderProgram);

        // Create transformations
        glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 1000.0f);
        glm::mat4 model = glm::mat4(1.0f);

        // Set matrices in shader
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Draw buildings
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Clean up
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

GLFWwindow* initializeWindow() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return nullptr;
    }

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    GLFWwindow* window = glfwCreateWindow(800, 600, "City Landscape", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    return window;
}

unsigned int compileShaders() {
    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check for vertex shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    // Fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check for fragment shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    // Link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 0;
    }

    // Delete shaders as they're linked into program and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

void generateCity(std::vector<Building>& buildings, int numBuildings) {
    // Random number generation
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_real_distribution<float> posDistX(-100.0f, 100.0f);
    std::uniform_real_distribution<float> posDistZ(-100.0f, 100.0f);
    std::uniform_real_distribution<float> sizeDistWidth(5.0f, 15.0f);
    std::uniform_real_distribution<float> sizeDistDepth(5.0f, 15.0f);
    std::uniform_real_distribution<float> heightDist(10.0f, 60.0f);
    std::uniform_real_distribution<float> colorDist(0.2f, 0.8f);

    // Generate buildings with random properties
    for (int i = 0; i < numBuildings; i++) {
        Building building;
        building.position = glm::vec3(posDistX(rng), 0.0f, posDistZ(rng));
        building.width = sizeDistWidth(rng);
        building.depth = sizeDistDepth(rng);
        building.height = heightDist(rng);

        // Night city colors - blues, purples, etc.
        if (i % 5 == 0) {
            // Make some buildings emit more light (bright colors)
            building.color = glm::vec3(colorDist(rng) * 0.5f + 0.5f, 
                                      colorDist(rng) * 0.5f + 0.5f, 
                                      colorDist(rng) * 0.5f + 0.5f);
        } else {
            // Regular buildings, more muted colors
            building.color = glm::vec3(colorDist(rng) * 0.3f, 
                                      colorDist(rng) * 0.3f, 
                                      colorDist(rng) * 0.5f + 0.3f);
        }

        buildings.push_back(building);
    }

    // Add ground plane
    Building ground;
    ground.position = glm::vec3(0.0f, -0.5f, 0.0f);
    ground.width = 250.0f;
    ground.depth = 250.0f;
    ground.height = 1.0f;
    ground.color = glm::vec3(0.1f, 0.1f, 0.1f); // Dark gray
    buildings.push_back(ground);
}

void createBuildingBuffers(const std::vector<Building>& buildings, 
                          std::vector<float>& vertices, 
                          std::vector<unsigned int>& indices) {
    for (size_t i = 0; i < buildings.size(); i++) {
        const Building& b = buildings[i];
        
        // Calculate half dimensions for convenience
        float hw = b.width / 2.0f;
        float hh = b.height / 2.0f;
        float hd = b.depth / 2.0f;
        
        // Base index for this building
        unsigned int baseIndex = vertices.size() / 6;

        // Each vertex has: position (3 floats) + color (3 floats)
        // Define 8 vertices of the building (a cube)
        
        // Bottom vertices
        // Front-left
        vertices.push_back(b.position.x - hw); vertices.push_back(b.position.y - hh); vertices.push_back(b.position.z + hd);
        vertices.push_back(b.color.r); vertices.push_back(b.color.g); vertices.push_back(b.color.b);
        
        // Front-right
        vertices.push_back(b.position.x + hw); vertices.push_back(b.position.y - hh); vertices.push_back(b.position.z + hd);
        vertices.push_back(b.color.r); vertices.push_back(b.color.g); vertices.push_back(b.color.b);
        
        // Back-right
        vertices.push_back(b.position.x + hw); vertices.push_back(b.position.y - hh); vertices.push_back(b.position.z - hd);
        vertices.push_back(b.color.r); vertices.push_back(b.color.g); vertices.push_back(b.color.b);
        
        // Back-left
        vertices.push_back(b.position.x - hw); vertices.push_back(b.position.y - hh); vertices.push_back(b.position.z - hd);
        vertices.push_back(b.color.r); vertices.push_back(b.color.g); vertices.push_back(b.color.b);
        
        // Top vertices
        // Front-left
        vertices.push_back(b.position.x - hw); vertices.push_back(b.position.y + hh); vertices.push_back(b.position.z + hd);
        vertices.push_back(b.color.r + 0.1f); vertices.push_back(b.color.g + 0.1f); vertices.push_back(b.color.b + 0.1f);
        
        // Front-right
        vertices.push_back(b.position.x + hw); vertices.push_back(b.position.y + hh); vertices.push_back(b.position.z + hd);
        vertices.push_back(b.color.r + 0.1f); vertices.push_back(b.color.g + 0.1f); vertices.push_back(b.color.b + 0.1f);
        
        // Back-right
        vertices.push_back(b.position.x + hw); vertices.push_back(b.position.y + hh); vertices.push_back(b.position.z - hd);
        vertices.push_back(b.color.r + 0.1f); vertices.push_back(b.color.g + 0.1f); vertices.push_back(b.color.b + 0.1f);
        
        // Back-left
        vertices.push_back(b.position.x - hw); vertices.push_back(b.position.y + hh); vertices.push_back(b.position.z - hd);
        vertices.push_back(b.color.r + 0.1f); vertices.push_back(b.color.g + 0.1f); vertices.push_back(b.color.b + 0.1f);
        
        // Define the 12 triangles (6 faces, 2 triangles per face)
        // Bottom face
        indices.push_back(baseIndex + 0); indices.push_back(baseIndex + 1); indices.push_back(baseIndex + 2);
        indices.push_back(baseIndex + 2); indices.push_back(baseIndex + 3); indices.push_back(baseIndex + 0);
        
        // Top face
        indices.push_back(baseIndex + 4); indices.push_back(baseIndex + 7); indices.push_back(baseIndex + 6);
        indices.push_back(baseIndex + 6); indices.push_back(baseIndex + 5); indices.push_back(baseIndex + 4);
        
        // Front face
        indices.push_back(baseIndex + 0); indices.push_back(baseIndex + 4); indices.push_back(baseIndex + 5);
        indices.push_back(baseIndex + 5); indices.push_back(baseIndex + 1); indices.push_back(baseIndex + 0);
        
        // Right face
        indices.push_back(baseIndex + 1); indices.push_back(baseIndex + 5); indices.push_back(baseIndex + 6);
        indices.push_back(baseIndex + 6); indices.push_back(baseIndex + 2); indices.push_back(baseIndex + 1);
        
        // Back face
        indices.push_back(baseIndex + 2); indices.push_back(baseIndex + 6); indices.push_back(baseIndex + 7);
        indices.push_back(baseIndex + 7); indices.push_back(baseIndex + 3); indices.push_back(baseIndex + 2);
        
        // Left face
        indices.push_back(baseIndex + 3); indices.push_back(baseIndex + 7); indices.push_back(baseIndex + 4);
        indices.push_back(baseIndex + 4); indices.push_back(baseIndex + 0); indices.push_back(baseIndex + 3);
    }
}

void processInput(GLFWwindow* window, glm::vec3& cameraPos, glm::vec3& cameraFront) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // Camera movement
    float cameraSpeed = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, glm::vec3(0.0f, 1.0f, 0.0f))) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        cameraPos += glm::vec3(0.0f, cameraSpeed, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        cameraPos -= glm::vec3(0.0f, cameraSpeed, 0.0f);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}