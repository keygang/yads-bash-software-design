#include "bash.hpp"

namespace bash {

Bash::Bash() : variables_(std::make_shared<Variables>()), parser_(variables_) {}

void bash::Bash::run() {
  while (true) {
    std::string line;
    std::getline(std::cin, line);
    auto [command, args] = parser_.parse(line);
    if (command == nullptr) {
      std::cerr << "Unknown command\n";
      continue;
    }
    auto resp = command->run(args);
    std::cout << resp.output << "\n";
  }
}

}  // namespace bash
