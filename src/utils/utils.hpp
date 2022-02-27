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
    file.close();
    return {true, data};
  }
  return {false, ""};
}

std::tuple<bool, std::string> count_file(const std::string& file_name) {
  std::ifstream file(file_name);

  char buffer[1];
  enum states { WHITESPACE, WORD };
  int state = WHITESPACE;
  int wordCount = 0;
  int cc = 0;
  int lc = 0;

  if (file.is_open()) {
    while (file.read(buffer, 1))
    {
      cc++;
      if (buffer[0] == '\n') {
        lc++;
      }
      if (isspace(static_cast<unsigned char>(buffer[0])) == 0)
      {
        if (state == WHITESPACE)
        {
          wordCount++;
          state = WORD;
        }
      }
      else
      {
        state = WHITESPACE;
      }
    }
    file.close();
    if (wordCount) {
      ++lc;
    }
    auto cc_str = std::to_string(cc);
    auto lc_str = std::to_string(lc);
    auto wc_str = std::to_string(wordCount);

    auto data = lc_str + " " + wc_str + " " + cc_str + " " + file_name;
    return {true, data};
  }
  return {false, ""};
}

}  // namespace utils

}  // namespace bash