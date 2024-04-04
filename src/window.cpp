// Windowing system

#include "window.hpp"

#include <stdexcept>

namespace mimic {
	Window::Window(uint32_t width, uint32_t height, const char* title) {
		if (!glfwInit()) {
			throw std::runtime_error("GLFW: This platform is not supported.");
		}

		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		glfwWindowHint(GLFW_RESIZABLE, false);

		this->window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	}

	Window::~Window() {
		glfwDestroyWindow(this->window);
		glfwTerminate();
	}

	void Window::close() {
		glfwWindowShouldClose(this->window);
	}

	bool Window::should_close() {
		return glfwWindowShouldClose(this->window);
	}

	void Window::poll_events() {
		glfwPollEvents();
	}
}  // namespace mimic