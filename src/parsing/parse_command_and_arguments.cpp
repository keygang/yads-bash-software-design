#include "parse_command_and_arguments.hpp"

#include <algorithm>
#include <iostream>

#include "../utils/filesystem.hpp"
#include "../utils/utils.hpp"

namespace bash {

namespace parsing {

namespace {

void removeEmptyArgs(command::Arguments& args) {
  command::Arguments new_args;
  for (const auto& arg : args) {
    if (!arg.empty()) {
      new_args.push_back(arg);
    }
  }
  args = new_args;
}

}  // namespace

std::tuple<command::Command, command::Arguments>
ParseCommandAndArguments::parse(std::string line) {
  line = substitution(line);

  size_t first_not_space = 0;
  while (std::isspace(line[first_not_space]) != 0 &&
         first_not_space < line.size()) {
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
      auto var = commandStr.substr(0, equal_sign_pos);
      auto value = commandStr.substr(equal_sign_pos + 1, commandStr.size());
      return {std::make_shared<command::Assignment>(variables_), {var, value}};
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
  if (commandStr == command::Ls().name()) {
    return {std::make_shared<command::Ls>(), std::move(args)};
  }
  if (commandStr == command::Cd().name()) {
    return {std::make_shared<command::Cd>(), std::move(args)};
  }

  if (fs::exists(commandStr) && utils::is_file_executable(commandStr)) {
    return {std::make_shared<command::ExternalCommand>(commandStr, variables_),
            std::move(args)};
  }

  return {nullptr, {}};
}

ParseCommandAndArguments::ParseCommandAndArguments(
    std::shared_ptr<Variables> variables)
    : variables_(std::move(variables)) {}

std::string ParseCommandAndArguments::substitution(const std::string& line) {
  std::string new_line;
  for (size_t i = 0; i < line.size(); ++i) {
    if (line[i] == '\'') {
      new_line += line[i];
      i += 1;
      while (i < line.size() && line[i] != '\'') {
        new_line += line[i];
        i += 1;
      }
      new_line += line[i];
      continue;
    }
    if (line[i] == '$') {
      i += 1;
      std::string var_name;
      while (i < line.size() && std::isspace(line[i]) == 0 &&
             kQuotes.count(line[i]) == 0 && line[i] != '$') {
        var_name += line[i];
        i += 1;
      }
      new_line += (*variables_)[var_name];
      i -= 1;
      continue;
    }
    new_line += line[i];
  }
  return new_line;
}

}  // namespace parsing
}  // namespace bash