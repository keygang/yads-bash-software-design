#include "command.hpp"

#include <experimental/filesystem>
#include <iostream>
#include <numeric>
#include <tuple>

#include "../utils/utils.hpp"

namespace bash {
namespace command {

CommandResponse Echo::run(const Arguments& args) {
  std::string out = utils::join(args, " ");
  return CommandResponse{.output = out, .status_code = 0};
}

std::string Echo::name() const { return "echo"; }

CommandResponse Exit::run(const Arguments& args) {
  std::ignore = args;
  exit(0);
}

std::string Exit::name() const { return "exit"; }

std::string Cat::name() const { return "cat"; }

CommandResponse Cat::run(const Arguments& args) {
  std::string tot_data;
  int any_open = 1;
  for (const auto& arg : args) {
    auto [is_open, data] = utils::read_file(arg);
    if (is_open) {
      any_open = 0;
      if (!tot_data.empty()) {
        tot_data += "\n";
      }
       tot_data += data;
    }
  }
  return {tot_data, any_open};
}

CommandResponse Wc::run(const Arguments& args) {
  std::string tot_data;
  std::string data;
  int any_open = 1;
  for (const auto& arg : args) {
    auto [is_open, lineCount, wordCount, byteCount] = utils::count_lines_words_bytes(arg);
    if (is_open) {
      data = std::to_string(lineCount) + " " + std::to_string(wordCount) +
             " " + std::to_string(byteCount) + " " + arg;
      any_open = 0;
      if (!tot_data.empty()) {
        tot_data += "\n";
      }
      tot_data += data;
    }
  }
  return {tot_data, any_open};
}

std::string Wc::name() const { return "wc"; }

CommandResponse Pwd::run(const Arguments& args) {
  std::ignore = args;
  return {std::experimental::filesystem::current_path().string(), 0};
}

std::string Pwd::name() const { return "pwd"; }

CommandResponse Assignment::run(const Arguments& args) {
  return {(args[0] + args[1]), 0};
}

std::string Assignment::name() const { return "assignment"; }
}  // namespace command
}  // namespace bash
