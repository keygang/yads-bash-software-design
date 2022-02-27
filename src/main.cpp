#include <iostream>
#include <unordered_map>

#include "parsing/parser.hpp"

namespace bash {

[[noreturn]] void run() {
  parsing::Parser parser;
  std::unordered_map<std::string, std::string> variables;

  while (true) {
    std::string line;
    std::getline(std::cin, line);
    auto [command, args] = parser.parse(line);
    if (command == nullptr) {
      std::cerr << "Unknown command\n";
      continue;
    }
    if (command->name() == "assignment") {
      variables[args[0]] = args[1];
      continue;
    }
    auto resp = command->run(args);
    std::cout << resp.output << "\n";
  }
}

}  // namespace bash

int main() {
  bash::run();

  return 0;
}