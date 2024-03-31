#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#  define MIMIC_EXPORT __declspec(dllexport)
#else
#  define MIMIC_EXPORT
#endif

MIMIC_EXPORT void mimic();
MIMIC_EXPORT void mimic_print_vector(const std::vector<std::string>& strings);
