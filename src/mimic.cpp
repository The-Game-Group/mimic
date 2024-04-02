// Test entry point

// #define GLAD_VULKAN_IMPLEMENTATION
// #include <glad/vulkan.h>

#include "mimic.hpp"

const uint32_t WIDTH = 1920;
const uint32_t HEIGHT = 1080;

namespace mimic {
Engine::Engine(const char* application_name)
    : client_name{application_name}, window(WIDTH, HEIGHT, application_name) {}

Engine::~Engine() {
  this->window.close();
}

void Engine::run() {
  while (!this->window.should_close()) {
    this->window.poll_events();
  }
}

}  // namespace mimic