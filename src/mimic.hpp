#pragma once

#include "window.hpp"

namespace mimic {
	class Engine {
	 public:
		Engine(const char* application_name);
		~Engine();

		void run();

	 private:
		const char*   client_name;
		mimic::Window window;
	};
}  // namespace mimic