#pragma once

#include <fstream>
#include <string>
#include <tuple>
#include <vector>

#include "filesystem.hpp"

namespace bash {

namespace utils {

template <typename T>
std::string join(const std::vector<T>& array, const std::string& delimiter) {
  std::string s;
  for (size_t i = 0; i + 1 < array.size(); ++i) {
    s += array[i];
    s += delimiter;
  }
  if (!array.empty()) {
    s += array.back();
  }
  return s;
}

std::tuple<bool, std::string> read_file(const std::string& file_name);

size_t count_lines(const std::string& data);

size_t count_words(const std::string& data);

std::tuple<bool, size_t, size_t, size_t> count_lines_words_bytes(
    const std::string& file_name);

bool is_file_executable(const std::string& file_path);

}  // namespace utils
}  // namespace bash
