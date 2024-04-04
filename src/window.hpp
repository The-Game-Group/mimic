#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace mimic {
	class Window {
	 private:
		GLFWwindow* window;

	 public:
		Window(uint32_t width, uint32_t height, const char* title);
		~Window();

		void close();
		bool should_close();
		void poll_events();
	};
}  // namespace mimic