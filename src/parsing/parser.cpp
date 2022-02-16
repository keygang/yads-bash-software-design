#include "parser.hpp"

namespace bash {
namespace parsing {

std::tuple<command::Command, command::Arguments> bash::parsing::Parser::parse(
    const std::string& line) {
  return pca_.parse(line);
}

}  // namespace parsing
}  // namespace bash
