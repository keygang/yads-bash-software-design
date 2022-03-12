#include "utils.hpp"

namespace bash {
namespace utils {

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

size_t count_lines(const std::string& data) {
//  size_t lineCount = 0;
//  for (char letter : data) {
//    if (letter == '\n') {
//      ++lineCount;
//    }
//  }
//  if (!data.empty()) {
//    ++lineCount;
//  }
  return std::count(data.begin(), data.end(), '\n') + 1;
}

size_t count_words(const std::string& data) {
  size_t wordCount = 0;
  std::string currWord;
  for (char letter : data) {
    if (std::isspace(letter) == 0) {
      currWord += letter;
    } else {
      if (!currWord.empty()) {
        ++wordCount;
        currWord = "";
      }
    }
  }
  if (!currWord.empty()) {
    ++wordCount;
  }
  return wordCount;
}

bool is_file_executable(const std::string& file_path) {
  auto permissions = fs::status(file_path).permissions();
  return static_cast<bool>(
      permissions &
      (fs::perms::group_exec | fs::perms::owner_exec | fs::perms::others_exec));
}
}  // namespace utils
}  // namespace bash
