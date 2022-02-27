#pragma once

#include <unordered_map>
#include <iostream>
#include "../parsing/parser.hpp"

namespace bash {

class Bash {
public:
  void run();
private:
  parsing::Parser parser_;
  std::unordered_map<std::string, std::string> variables_;
};

}  // namespace bash