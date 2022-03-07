#include "bash.hpp"

#include "../utils/filesystem.hpp"

namespace bash {

namespace {

std::string hint() { return fs::current_path().filename().string() + " % "; }

}  // namespace

Bash::Bash(std::istream& in, std::ostream& out, std::ostream& err)
    : in_(in),
      out_(out),
      err_(err),
      variables_(std::make_shared<Variables>()),
      parser_(variables_) {}

void bash::Bash::run() {
  while (true) {
    out_ << hint();
    std::string line;
    std::getline(in_, line);
    auto pipeline = parser_.parse(line);
    auto response = executor_.execute(pipeline);
    if (response.err) {
      err_ << *response.err << std::endl;
    }
    if (response.output) {
      out_ << *response.output << std::endl;
    }
    if (response.status_code == command::CommandStatusCode::Exit) {
      break;
    }
  }
}

}  // namespace bash
