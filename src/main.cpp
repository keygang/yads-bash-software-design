#include "bash/bash.hpp"

int main() {
  bash::Config config;
  bash::Bash bash(config);
  bash.run();

  return 0;
}