#include "variables.hpp"

#include <fmt/format.h>

namespace bash {

std::string Variables::serialize() const {
  std::string serialized;
  for (const auto& [key, value] : *this) {
    if (!serialized.empty()) {
      serialized += " ";
    }
    serialized += fmt::format("{}={}", key, value);
  }
  return serialized;
}

}  // namespace bash
