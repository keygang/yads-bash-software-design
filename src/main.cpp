#include "bash/bash.hpp"

int main() {
  bash::Bash bash(std::cin, std::cout, std::cerr);
  bash.run();

  return 0;
}