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
  size_t first_not_space = 0;
  while (std::isspace(line[first_not_space]) != 0) {
    ++first_not_space;
  }

  std::string commandStr;
  command::Arguments args;
  std::string currArg;

  for (size_t i = first_not_space; i < line.size(); ++i) {

    if (line[i] == ' ' && commandStr.empty() && !currArg.empty()) {
      commandStr = currArg;
      currArg = "";
      continue;
    }
    if (line[i] == ' ') {
      args.push_back(currArg);
      currArg = "";
      continue;
    }
    if (line[i] == '\"' || line[i] == '\'') {
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
  if (commandStr.empty()) {
    commandStr = currArg;
  } else {
    args.push_back(currArg);
  }
  removeEmptyArgs(args);

  if (!commandStr.empty()) {
    auto equal_sign_pos = commandStr.find('=');
    if (equal_sign_pos != std::string::npos && line[first_not_space] != '\"' &&
        line[first_not_space] != '\'') {
      return {std::make_shared<command::Assignment>(),
          {commandStr.substr(0, equal_sign_pos),
               commandStr.substr(equal_sign_pos + 1, commandStr.size())}};
    }
  }

  if (commandStr == command::Exit().name()) {
    return {std::make_shared<command::Exit>(), {}};
  }
  if (commandStr == command::Echo().name()) {
    return {std::make_shared<command::Echo>(), std::move(args)};
  }
  if (commandStr == command::Cat().name()) {
    return {std::make_shared<command::Cat>(), std::move(args)};
  }
  if (commandStr == command::Pwd().name()) {
    return {std::make_shared<command::Pwd>(), std::move(args)};
  }
  if (commandStr == command::Wc().name()) {
    return {std::make_shared<command::Wc>(), std::move(args)};
  }

  return {nullptr, {}};
}

}  // namespace parsing
}  // namespace bash