#pragma once

#include <unordered_set>

#include "../bash/variables.hpp"
#include "../commands/arguments.hpp"
#include "../commands/command.hpp"

namespace bash {
namespace parsing {

const std::unordered_set<char> kQuotes = {'\'', '\"'};

class ParseCommandAndArguments {
public:
  /*
   * @param variables     переменные окружения bash'а
   */
  explicit ParseCommandAndArguments(std::shared_ptr<Variables> variables);
  /*
   * Парсит строчку в которой только ОДНА команда, и возращает команду с
   * аргументами (т. к. пока что фаза 1)
   *
   * @param  line         строка которую будем парсить
   * @return              tuple из команды и ее аргументов
   */
  std::tuple<command::Command, command::Arguments> parse(
      const std::string& line);

private:
  std::shared_ptr<Variables> variables_;
};

}  // namespace parsing
}  // namespace bash
