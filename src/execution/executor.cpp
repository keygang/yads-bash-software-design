#include "executor.hpp"

namespace bash {

namespace execution {

command::CommandResponse Executor::execute(const command::Pipeline& pipeline) {
  command::CommandResponse response;
  for (const auto& [command, args] : pipeline) {
    if (command != nullptr) {
      response = command->run(args, response.output);
    } else {
      response = command::CommandResponse{
          .output = std::nullopt, .err = "Unknown command", .status_code = 1};
    }
  }
  return response;
}

}  // namespace execution

}  // namespace bash