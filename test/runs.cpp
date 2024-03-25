#include "mimic/mimic.hpp"
#include <vector>
#include <string>
#include <catch2/catch_all.hpp>

TEST_CASE("Mimic runs.") {
    mimic();

    std::vector<std::string> vec;
    vec.push_back("test_package");

    // mimic_print_vector(vec);

    REQUIRE(vec.size() == 1);
}