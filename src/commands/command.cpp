#include "command.hpp"

#include <filesystem>
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
  if (args.size() != 1) {
    // TODO:
    return {"", 0};
  }
  auto [is_open, data] = utils::read_file(args[0]);
  return {data, is_open ? 1 : 0};
}

CommandResponse Pwd::run(const Arguments& args) {
  std::ignore = args;
  return {std::filesystem::current_path().string(), 0};
}

std::string Pwd::name() const { return "pwd"; }
}  // namespace command
}  // namespace bash
