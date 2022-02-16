#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace bash {

namespace utils {

template <typename T>
std::string join(const std::vector<T>& array,
                 const std::string& delimiter = " ") {
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

std::tuple<bool, std::string> read_file(const std::string& file_name) {
  std::ifstream file(file_name);
  if (file.is_open()) {
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    return {true, data};
  }
  return {false, ""};
}

}  // namespace utils

}  // namespace bash