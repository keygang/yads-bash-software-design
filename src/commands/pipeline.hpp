#include <commands/command.hpp>
#include <tuple>
#include <vector>

namespace bash {
namespace command {

using Pipeline = std::vector<std::tuple<Command, Arguments>>;

}  // namespace command
}  // namespace bash
