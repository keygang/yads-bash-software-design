#pragma once

#include <initializer_list>
#include <string>
#include <vector>
#include <execution>

namespace bash {

namespace command {

using Arguments = std::vector<std::string>;

class EmptyArgs : public std::runtime_error {
public:
  explicit EmptyArgs(const std::string& message);
};

}  // namespace command
}  // namespace bash
