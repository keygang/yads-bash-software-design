#pragma once

#include "../commands/arguments.hpp"
#include "../commands/command.hpp"
#include "parse_command_and_arguments.hpp"

namespace bash {
namespace parsing {

class ParserInterface {
public:
  virtual std::tuple<command::Command, command::Arguments> parse(
      const std::string& line) = 0;
};

class Parser : public ParserInterface {
public:
  std::tuple<command::Command, command::Arguments> parse(
      const std::string& line) override;

private:
  ParseCommandAndArguments pca_;
};

}  // namespace parsing
}  // namespace bash