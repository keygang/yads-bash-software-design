#include "bash.hpp"

namespace bash {

void bash::Bash::run(){
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
