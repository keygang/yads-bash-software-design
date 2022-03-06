#pragma once

#include <memory>

#include "../bash/variables.hpp"
#include "arguments.hpp"

namespace bash {
namespace command {

struct CommandResponse {
  std::string output;
  int status_code;
};

class CommandInterface {
public:
  virtual ~CommandInterface() = default;
  virtual CommandResponse run(const Arguments& args) = 0;
  virtual std::string name() const = 0;
};

class Echo : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Cat : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Exit : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Pwd : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Wc : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Ls : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Cd : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class ExternalCommand : public CommandInterface {
public:
  explicit ExternalCommand(std::string executable_file);
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;

private:
  std::string executable_file_;
};

class Assignment : public CommandInterface {
public:
  explicit Assignment(std::shared_ptr<Variables> variables);
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;

private:
  std::shared_ptr<Variables> variables_;
};

using Command = std::shared_ptr<CommandInterface>;

}  // namespace command
}  // namespace bash