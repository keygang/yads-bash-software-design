#include <commands/pipeline.hpp>

namespace bash {

namespace execution {

class ExecutorInterface {
public:
  virtual ~ExecutorInterface() = default;
  virtual command::CommandResponse execute(
      const command::Pipeline& pipeline) = 0;
};

class Executor : public ExecutorInterface {
public:
  command::CommandResponse execute(const command::Pipeline& pipeline) override;
};

}  // namespace execution

}  // namespace bash