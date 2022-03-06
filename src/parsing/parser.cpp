#include "parser.hpp"

namespace bash {
namespace parsing {

Parser::Parser(std::shared_ptr<Variables> variables)
    : variables_(std::move(variables)), pca_(variables_) {}

std::tuple<command::Command, command::Arguments> bash::parsing::Parser::parse(
    const std::string& line) {
  return pca_.parse(line);
}

}  // namespace parsing
}  // namespace bash
