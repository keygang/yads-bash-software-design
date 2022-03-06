#pragma once

#include <iostream>
#include <unordered_map>

#include "../parsing/parser.hpp"
#include "variables.hpp"

namespace bash {

/*
 * Класс Bash.
 */
class Bash {
public:
  Bash();
  /*
   * Начинает выполнение bash'а.
   * Закончить выполнени можно через команду exit, или завершить процесс
   * программы.
   */
  void run();

private:
  std::shared_ptr<Variables> variables_;
  parsing::Parser parser_;
};

}  // namespace bash