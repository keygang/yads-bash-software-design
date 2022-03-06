#include "parser.hpp"

namespace bash {
namespace parsing {

std::vector<std::string> splitCommands(const std::string& line) {
  bool is_in_quotes = false;
  char last_quote = '0';
  std::vector<std::string> splitted;
  std::string current_str;
  for (size_t i = 0; i <= line.size(); ++i) {
    if (kQuotes.count(line[i]) != 0) {
      if (is_in_quotes) {
        if (line[i] == last_quote) {
          is_in_quotes = false;
        }
      } else {
        is_in_quotes = true;
        last_quote = line[i];
      }
    }
    if (i == line.size() || (line[i] == '|' && !is_in_quotes)) {
      splitted.push_back(current_str);
      current_str = "";
    } else {
      current_str += line[i];
    }
  }
  return splitted;
}

Parser::Parser(std::shared_ptr<Variables> variables)
    : variables_(std::move(variables)), pca_(variables_) {}

command::Pipeline bash::parsing::Parser::parse(const std::string& line) {
  command::Pipeline pipeline;
  auto lines = splitCommands(line);
  for (const auto& str : lines) {
    auto command_and_args = pca_.parse(str);
    pipeline.push_back(command_and_args);
  }
  return pipeline;
}

}  // namespace parsing
}  // namespace bash
