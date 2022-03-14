#include <iostream>
#include <memory>

namespace bash {

/*
 * Определяет куда направлять потоки вывода, ошибок, показывать ли директорию,
 * в которой находишься
 */
struct Config {
  std::istream* in_stream = &std::cin;
  std::ostream* out_stream = &std::cout;
  std::ostream* err_stream = &std::cerr;

  bool show_hint = true;
};

}  // namespace bash
