#pragma once

#include <bash/config.hpp>
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
  Bash(Config config);
  /*
   * Начинает выполнение bash'а.
   * Закончить выполнени можно через команду exit, или завершить процесс
   * программы.
   */
  void run();

private:
  Config config_;

  std::shared_ptr<Variables> variables_;
  parsing::Parser parser_;
  execution::Executor executor_;
};

}  // namespace bash