#pragma once

#include "../bash/variables.hpp"
#include "../commands/arguments.hpp"
#include "../commands/command.hpp"
#include "parse_command_and_arguments.hpp"

namespace bash {
namespace parsing {

class ParserInterface {
public:
  virtual ~ParserInterface() = default;
  virtual std::tuple<command::Command, command::Arguments> parse(
      const std::string& line) = 0;
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
  std::tuple<command::Command, command::Arguments> parse(
      const std::string& line) override;

private:
  std::shared_ptr<Variables> variables_;
  ParseCommandAndArguments pca_;
};

}  // namespace parsing
}  // namespace bash