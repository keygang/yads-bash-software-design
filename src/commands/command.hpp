#pragma once

#include <memory>

#include "../bash/variables.hpp"
#include "arguments.hpp"

namespace bash {
namespace command {

/*
 * Поддерживается отдельный статус код Exit для тестирования команды exit
 */
enum class CommandStatusCode { Ok, ArgsFail, Unknown, Exit };

/*
 * То, что возвращает любая команда
 */
struct CommandResponse {
  bool operator==(const CommandResponse& other) const;

  std::optional<std::string> output;
  std::optional<std::string> err;
  CommandStatusCode status_code;
};

/*
 * Интерфейс команды
 * поле name - имя команды
 */
class CommandInterface {
public:
  virtual ~CommandInterface() = default;

  /*
   * Исполняет команду
   *
   * @param  user_args    вектрор аргументов
   * @param  pipe_arg     при наличии нескольких команд в пайплайне, output
   *                      предыдущей команды является pipe_arg выполняемой команды
   *
   * @return              CommandResponse команды
   */

  virtual CommandResponse run(
      const Arguments& user_args,
      const std::optional<std::string>& pipe_arg = std::nullopt) = 0;
  virtual std::string name() const = 0;
};

class Echo : public CommandInterface {
public:
  /*
   * Выводит аргументы в output, при наличии pipe_args, user_args игнорируются
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Cat : public CommandInterface {
public:
  /*
   * Выводит в output содержимое файла, при наличии pipe_args, user_args игнорируются,
   * название файла определяется первым аргументом, остальные аргументы игнорируются
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Exit : public CommandInterface {
public:
  /*
   * Завершает Bash
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Pwd : public CommandInterface {
public:
  /*
   * Выводит в output текущую директорию, аргументы игнорируются
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Wc : public CommandInterface {
public:
  /*
   * Выводит в output количество строк, слов и байт в введенном тексте,
   * или в файле, если он указан
   *
   * если pipe_arg пуст, название файла определяется первым аргументом (user_args[0]),
   * остальные аргументы игнорируются
   *
   * если pipe_arg не пуст, выводится количество строк, слов и байт в pipe_arg
   *
   * пустая строка учитывается при подсчете строк
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Ls : public CommandInterface {
public:
  /*
   * Выводит в output содержимое текущей директории
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Cd : public CommandInterface {
public:
  /*
   * Осуществляет переход в другую директорию, определяемую user_args[0],
   * остальные аргументы игнорируются, pipe_arg игнорируется
   */
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

/*
 * Вызов внешней команды
 */
class ExternalCommand : public CommandInterface {
public:
  explicit ExternalCommand(std::string executable_file,
                           std::shared_ptr<Variables> variables);
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;

  std::string serialize();

  std::string name() const override;

private:
  std::string executable_file_;
  std::shared_ptr<Variables> variables_;
};

/*
 * Оператор присваивания
 */
class Assignment : public CommandInterface {
public:
  explicit Assignment(std::shared_ptr<Variables> variables);
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;

private:
  std::shared_ptr<Variables> variables_;
};

using Command = std::shared_ptr<CommandInterface>;

}  // namespace command
}  // namespace bash