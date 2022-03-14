#include "executor.hpp"

namespace bash {

namespace execution {

command::CommandResponse Executor::execute(const command::Pipeline& pipeline) {
  command::CommandResponse response;
  for (const auto& [command, args] : pipeline) {
    if (command != nullptr) {
      response = command->run(args, response.output);
      if (response.status_code == command::CommandStatusCode::Exit) {
        return response;
      }
   } else {
      response = command::CommandResponse{
          .output = std::nullopt,
          .err = "Unknown command",
          .status_code = command::CommandStatusCode::Unknown};
    }
  }
  return response;
}

}  // namespace execution

}  // namespace bash