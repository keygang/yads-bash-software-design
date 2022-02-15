#include "command.hpp"

#include <numeric>
#include <tuple>

namespace bash {
namespace command {

CommandResponse Echo::run(const Arguments& arg) {
  std::string out;
  for (size_t i = 0; i + 1 < arg.size(); ++i) {
    out += arg[i] + " ";
  }
  if (!arg.empty()) {
    out += arg.back();
  }
  return CommandResponse{.output = out, .status_code = 0};
}

std::string Echo::name() const { return "echo"; }

CommandResponse Exit::run(const Arguments& args) {
  std::ignore = args;
  exit(0);
}

std::string Exit::name() const { return "exit"; }

}  // namespace command
}  // namespace bash
