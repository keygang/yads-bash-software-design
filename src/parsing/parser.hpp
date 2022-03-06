#pragma once

#include <bash/variables.hpp>
#include <commands/arguments.hpp>
#include <commands/command.hpp>
#include <commands/pipeline.hpp>
#include <parsing/parse_command_and_arguments.hpp>

namespace bash {
namespace parsing {

std::vector<std::string> splitCommands(const std::string& line);

class ParserInterface {
public:
  virtual ~ParserInterface() = default;
  virtual command::Pipeline parse(const std::string& line) = 0;
};

class Parser : public ParserInterface {
public:
  /*
   * @param variables     переменные окружения bash'а
   */
  explicit Parser(std::shared_ptr<Variables> variables);
  /*
   * Парсит строчку, и возращает команду с аргументами (т. к. пока что фаза 1)
   *
   * @param  line         строка которую будем парсить
   * @return              tuple из команды и ее аргументов
   */
  command::Pipeline parse(const std::string& line) override;

private:
  std::shared_ptr<Variables> variables_;
  ParseCommandAndArguments pca_;
};

}  // namespace parsing
}  // namespace bash