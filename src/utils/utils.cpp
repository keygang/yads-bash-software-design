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
  size_t lineCount = 0;
  for (char letter : data) {
    if (letter == '\n') {
      ++lineCount;
    }
  }
  if (!data.empty()) {
    ++lineCount;
  }
  return lineCount;
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

std::tuple<bool, size_t, size_t, size_t> count_lines_words_bytes(const std::string& file_name) {
  auto [is_open, data] = utils::read_file(file_name);
  size_t wordCount = 0;
  size_t lineCount = 0;
  size_t byteCount = 0;
  if (is_open) {
    wordCount = count_words(data);
    lineCount = count_lines(data);
    byteCount = data.size();
  }
  return {is_open, lineCount, wordCount, byteCount};
}
}  // namespace utils
}  // namespace bash
