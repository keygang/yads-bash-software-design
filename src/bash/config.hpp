#include <iostream>
#include <memory>

namespace bash {

struct Config {
  std::istream* in_stream = &std::cin;
  std::ostream* out_stream = &std::cout;
  std::ostream* err_stream = &std::cerr;

  bool show_hint = true;
};

}  // namespace bash
