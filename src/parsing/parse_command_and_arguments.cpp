#include "parse_command_and_arguments.hpp"

#include <algorithm>
#include <iostream>

namespace bash {

namespace parsing {

namespace {

void removeEmptyArgs(command::Arguments& args) {
  command::Arguments new_args;
  for (const auto& arg : args) {
    if (!arg.empty()) {
      new_args.push_back(std::move(arg));
    }
  }
  args = new_args;
}

}  // namespace

std::tuple<command::Command, command::Arguments>
ParseCommandAndArguments::parse(const std::string& line) {
  auto end_command_pos = line.find(" ");
  if (end_command_pos == std::string::npos) {
    end_command_pos = line.size();
  }
  auto commandStr = line.substr(0, end_command_pos);
  if (commandStr == command::Exit().name()) {
    return {std::make_shared<command::Exit>(), {}};
  }

  command::Arguments args;
  std::string currArg;
  for (size_t i = end_command_pos; i < line.size(); ++i) {
    if (line[i] == ' ') {
      args.push_back(currArg);
      currArg = "";
      continue;
    }
    if (line[i] == '\"' || line[i] == '\'') {
      args.push_back(currArg);
      currArg = "";
      auto start_index = i;
      i += 1;
      while (line[i] != line[start_index]) {
        currArg += line[i];
        i += 1;
      }
    } else {
      currArg += line[i];
    }
  }
  args.push_back(currArg);
  removeEmptyArgs(args);

  if (commandStr == command::Echo().name()) {
    return {std::make_shared<command::Echo>(), std::move(args)};
  }
  if (commandStr == command::Cat().name()) {
    return {std::make_shared<command::Cat>(), std::move(args)};
  }
  if (commandStr == command::Pwd().name()) {
    return {std::make_shared<command::Pwd>(), std::move(args)};
  }
  return {nullptr, {}};
}

}  // namespace parsing
}  // namespace bash