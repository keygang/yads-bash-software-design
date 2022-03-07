#include "command.hpp"

#include <fmt/format.h>

#include <tuple>
#include <utility>

#include "../utils/filesystem.hpp"
#include "../utils/utils.hpp"

namespace bash {
namespace command {

CommandResponse Echo::run(const Arguments& args,
                          const std::optional<std::string>& pipe_arg) {
  const auto& command_args = pipe_arg ? Arguments{*pipe_arg} : args;
  std::string out = fmt::format("{}", fmt::join(command_args, " "));
  return CommandResponse{
      .output = out, .err = std::nullopt, .status_code = CommandStatusCode::Ok};
}

std::string Echo::name() const { return "echo"; }

CommandResponse Exit::run(const Arguments& args,
                          const std::optional<std::string>& pipe_arg) {
  std::ignore = args;
  std::ignore = pipe_arg;
  return {{}, {}, CommandStatusCode::Exit};
}

std::string Exit::name() const { return "exit"; }

std::string Cat::name() const { return "cat"; }

CommandResponse Cat::run(const Arguments& args,
                         const std::optional<std::string>& pipe_arg) {
  const auto& command_args = pipe_arg ? Arguments{*pipe_arg} : args;
  if (command_args.empty()) {
    return {{}, "Enter the file please", CommandStatusCode::ArgsFail};
  }

  auto [is_open, data] = utils::read_file(command_args[0]);
  if (is_open) {
    return CommandResponse{data, {}, CommandStatusCode::Ok};
  }
  return {{},
          fmt::format("Can't open file {}", command_args[0]),
          CommandStatusCode::ArgsFail};
}

CommandResponse Wc::run(const Arguments& args,
                        const std::optional<std::string>& pipe_arg) {
  std::string data;
  if (pipe_arg) {
    data = *pipe_arg;
  } else {
    if (args.empty()) {
      return {std::nullopt, "Enter the file please",
              CommandStatusCode::ArgsFail};
    }
    auto [is_ok, file_data] = utils::read_file(args[0]);
    if (!is_ok) {
      return {std::nullopt, fmt::format("Can't open file {}", args[0]),
              CommandStatusCode::ArgsFail};
    }
    data = std::move(file_data);
  }
  auto lines = utils::count_lines(data);
  auto words = utils::count_words(data);
  auto bytes = data.size();
  auto output = fmt::format("\t{}\t{}\t{}", lines, words, bytes);

  return {output, {}, CommandStatusCode::Ok};
}

std::string Wc::name() const { return "wc"; }

CommandResponse Pwd::run(const Arguments& args,
                         const std::optional<std::string>& pipe_arg) {
  std::ignore = args;
  std::ignore = pipe_arg;
  return {fs::current_path().string(), {}, CommandStatusCode::Ok};
}

std::string Pwd::name() const { return "pwd"; }

CommandResponse Assignment::run(const Arguments& args,
                                const std::optional<std::string>& pipe_arg) {
  std::ignore = pipe_arg;
  variables_->operator[](args[0]) = args[1];
  return {{}, std::nullopt, CommandStatusCode::Ok};
}

std::string Assignment::name() const { return "assignment"; }

Assignment::Assignment(std::shared_ptr<Variables> variables)
    : variables_(std::move(variables)) {}

std::string ExternalCommand::name() const { return executable_file_; }

ExternalCommand::ExternalCommand(std::string executable_file)
    : executable_file_(std::move(executable_file)) {}

CommandResponse ExternalCommand::run(
    const Arguments& args, const std::optional<std::string>& pipe_arg) {
  std::ignore = pipe_arg;
  auto command = fmt::format("{} {}", executable_file_, fmt::join(args, " "));
  auto status_code = system(command.c_str());
  return {
      {},
      {},
      status_code == 0 ? CommandStatusCode::Ok : CommandStatusCode::Unknown};
}

std::string Ls::name() const { return "ls"; }

CommandResponse Ls::run(const Arguments& args,
                        const std::optional<std::string>& pipe_arg) {
  std::ignore = args;
  std::ignore = pipe_arg;
  std::vector<std::string> files;
  for (const auto& file : fs::directory_iterator(fs::current_path())) {
    files.push_back(file.path().filename().string());
  }
  auto files_str = fmt::format("{}", fmt::join(files, "\n"));
  return {files_str, {}, CommandStatusCode::Ok};
}

std::string Cd::name() const { return "cd"; }

CommandResponse Cd::run(const Arguments& args,
                        const std::optional<std::string>& pipe_arg) {
  std::ignore = pipe_arg;
  fs::current_path(args[0]);
  return {{}, {}, CommandStatusCode::Ok};
}

bool CommandResponse::operator==(const CommandResponse& other) const {
  return std::make_tuple(output, err, status_code) ==
         std::make_tuple(other.output, other.err, other.status_code);
}
}  // namespace command
}  // namespace bash
