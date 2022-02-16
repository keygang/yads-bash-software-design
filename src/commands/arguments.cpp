#include "arguments.hpp"

namespace bash {

namespace command {

EmptyArgs::EmptyArgs(const std::string& message)
    : std::runtime_error(message) {}

}  // namespace command
}  // namespace bash
