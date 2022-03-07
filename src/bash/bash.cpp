#include "bash.hpp"

#include "../utils/filesystem.hpp"

namespace bash {

namespace {

std::string hint() { return fs::current_path().filename().string() + " % "; }

}  // namespace

Bash::Bash(std::istream& in)
    : in_(in), variables_(std::make_shared<Variables>()), parser_(variables_) {}

void bash::Bash::run() {
  while (true) {
    std::cout << hint();
    std::string line;
    std::getline(in_, line);
    auto pipeline = parser_.parse(line);
    auto response = executor_.execute(pipeline);
    if (response.err) {
      std::cerr << *response.err << std::endl;
    }
    if (response.output) {
      std::cout << *response.output << std::endl;
    }
    if (response.status_code == command::CommandStatusCode::Exit) {
      break;
    }
  }
}

}  // namespace bash
