#include "bash.hpp"

#include <utils/filesystem.hpp>

namespace bash {

namespace {

std::string hint() { return fs::current_path().filename().string() + " % "; }

}  // namespace

Bash::Bash(Config config)
    : config_(config),
      variables_(std::make_shared<Variables>()),
      parser_(variables_) {}

void bash::Bash::run() {
  while (true) {
    if (config_.show_hint) {
      *config_.out_stream << hint();
    }
    std::string line;
    std::getline(*config_.in_stream, line);
    auto pipeline = parser_.parse(line);
    auto response = executor_.execute(pipeline);
    if (response.err) {
      *config_.err_stream << *response.err << std::endl;
    }
    if (response.output) {
      *config_.out_stream << *response.output << std::endl;
    }
    if (response.status_code == command::CommandStatusCode::Exit) {
      break;
    }
  }
}

}  // namespace bash
