#pragma once

#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

#include "filesystem.hpp"

namespace bash {

namespace utils {

std::tuple<bool, std::string> read_file(const std::string& file_name);

size_t count_lines(const std::string& data);

size_t count_words(const std::string& data);

bool is_file_executable(const std::string& file_path);

}  // namespace utils
}  // namespace bash
