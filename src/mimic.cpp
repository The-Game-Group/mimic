// Test entry point

#define GLAD_VULKAN_IMPLEMENTATION
#include <glad/vulkan.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#include "vars.hpp"

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

GLFWwindow* initWindow() {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

  return glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
}

void runLoop(GLFWwindow* window) {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }
}

void cleanup(GLFWwindow* window) {
  glfwDestroyWindow(window);
  glfwTerminate();
}

int run() {
  mimic();

  GLFWwindow* window;

  try {
    window = initWindow();
    runLoop(window);
    cleanup(window);
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}