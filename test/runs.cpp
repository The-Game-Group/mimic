#include "mimic/mimic.hpp"
#include <catch2/catch_all.hpp>
#include <string>
#include <vector>

TEST_CASE("Mimic runs.") {
  mimic();

  std::vector<std::string> vec;
  vec.push_back("test_package");

  // mimic_print_vector(vec);

  REQUIRE(vec.size() == 1);
}