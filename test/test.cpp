
#include <build_info.hpp>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <mimic.hpp>
#include <ostream>

int main() {
  mimic::print_debug();

  try {
    mimic::Engine engine("Vulkan Demo");

    engine.run();
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}