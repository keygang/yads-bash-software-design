#pragma once

#include <bash/variables.hpp>
#include <execution/executor.hpp>
#include <iostream>
#include <parsing/parser.hpp>
#include <unordered_map>

namespace bash {

/*
 * Класс Bash.
 */
class Bash {
public:
  Bash(std::istream& in, std::ostream& out, std::ostream& err);
  /*
   * Начинает выполнение bash'а.
   * Закончить выполнени можно через команду exit, или завершить процесс
   * программы.
   */
  void run();

private:
  std::istream& in_;
  std::ostream& out_;
  std::ostream& err_;

  std::shared_ptr<Variables> variables_;
  parsing::Parser parser_;
  execution::Executor executor_;
};

}  // namespace bash