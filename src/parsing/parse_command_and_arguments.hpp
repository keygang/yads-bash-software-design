#pragma once

#include "../commands/arguments.hpp"
#include "../commands/command.hpp"

namespace bash {
namespace parsing {

class ParseCommandAndArguments {
public:
  std::tuple<command::Command, command::Arguments> parse(
      const std::string& line);
};

}  // namespace parsing
}  // namespace bash
