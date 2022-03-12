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
 * метод run отвечает за логику исполнения
 * поле name - имя команды
 */
class CommandInterface {
public:
  virtual ~CommandInterface() = default;
  virtual CommandResponse run(
      const Arguments& user_args,
      const std::optional<std::string>& pipe_arg = std::nullopt) = 0;
  virtual std::string name() const = 0;
};

class Echo : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Cat : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Exit : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Pwd : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Wc : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Ls : public CommandInterface {
public:
  CommandResponse run(const Arguments& user_args,
                      const std::optional<std::string>& pipe_arg) override;
  std::string name() const override;
};

class Cd : public CommandInterface {
public:
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