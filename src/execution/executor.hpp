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
  /*
   * Исполняет pipeline
   *
   * В цикле исполняет команды, передает значение output предыдущей команды
   * в качестве аргументов для следующей команды
   *
   * @param  pipeline     вектор tuple из команды и ее аргументов
   * @return              CommandResponse команды, выполненной последней
   */
  command::CommandResponse execute(const command::Pipeline& pipeline) override;
};

}  // namespace execution

}  // namespace bash