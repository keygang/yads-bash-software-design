#include "command.hpp"

#include <numeric>

namespace bash {
namespace command {

CommandResponse Echo::run(const Arguments& arg) {
  std::string out = std::accumulate(arg.begin(), arg.end(), std::string());
  return CommandResponse{.output = out, .status_code = 0};
}

}
}

