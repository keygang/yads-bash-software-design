#include "command.hpp"

#include <tuple>
#include <utility>

#include "../utils/filesystem.hpp"
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
  std::string tot_data;
  int any_open = 1;
  for (const auto& arg : args) {
    auto [is_open, data] = utils::read_file(arg);
    if (is_open) {
      any_open = 0;
      if (!tot_data.empty()) {
        tot_data += "\n";
      }
      tot_data += data;
    }
  }
  return {tot_data, any_open};
}

CommandResponse Wc::run(const Arguments& args) {
  std::string total_data;
  std::string data;
  int any_open = 1;
  for (const auto& arg : args) {
    auto [is_open, lineCount, wordCount, byteCount] =
        utils::count_lines_words_bytes(arg);
    if (is_open) {
      data = std::to_string(lineCount) + " " + std::to_string(wordCount) + " " +
             std::to_string(byteCount) + " " + arg;
      any_open = 0;
      if (!total_data.empty()) {
        total_data += "\n";
      }
      total_data += data;
    }
  }
  return {total_data, any_open};
}

std::string Wc::name() const { return "wc"; }

CommandResponse Pwd::run(const Arguments& args) {
  std::ignore = args;
  return {fs::current_path().string(), 0};
}

std::string Pwd::name() const { return "pwd"; }

CommandResponse Assignment::run(const Arguments& args) {
  variables_->operator[](args[0]) = args[1];
  return {"", 0};
}

std::string Assignment::name() const { return "assignment"; }

Assignment::Assignment(std::shared_ptr<Variables> variables)
    : variables_(std::move(variables)) {}

std::string ExternalCommand::name() const { return executable_file_; }

ExternalCommand::ExternalCommand(std::string executable_file)
    : executable_file_(std::move(executable_file)) {}

CommandResponse ExternalCommand::run(const Arguments& args) {
  auto command = "./" + executable_file_ + " " + utils::join(args, " ");
  auto status_code = system(command.c_str());
  return {"", status_code};
}

std::string Ls::name() const { return "ls"; }

CommandResponse Ls::run(const Arguments& args) {
  std::ignore = args;
  std::vector<std::string> files;
  for (const auto& file : fs::directory_iterator(fs::current_path())) {
    files.push_back(file.path().filename().string());
  }
  return {utils::join(files, "\n"), 0};
}

std::string Cd::name() const { return "cd"; }

CommandResponse Cd::run(const Arguments& args) {
  fs::current_path(args[0]);
  return {"", 0};
}

}  // namespace command
}  // namespace bash
