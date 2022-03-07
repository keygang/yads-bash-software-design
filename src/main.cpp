#include "bash/bash.hpp"

int main() {
  bash::Bash bash(std::cin);
  bash.run();

  return 0;
}