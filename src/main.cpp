#include <iostream>

#include "parsing/parser.hpp"

namespace bash {

[[noreturn]] void run() {
  parsing::Parser parser;

  while (true) {
    std::string line;
    std::getline(std::cin, line);
    auto [command, args] = parser.parse(line);
    auto resp = command->run(args);
    std::cout << resp.output << "\n";
  }
}

}  // namespace bash

int main() {
  bash::run();

  return 0;
}