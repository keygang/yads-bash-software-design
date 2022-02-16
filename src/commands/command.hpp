#pragma once

#include "arguments.hpp"

#include <memory>

namespace bash {
namespace command {

struct CommandResponse {
  std::string output;
  int status_code;
};

class CommandInterface {
public:
  virtual CommandResponse run(const Arguments& args) = 0;
  virtual std::string name() const = 0;
};

class Echo : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

class Exit : public CommandInterface {
public:
  CommandResponse run(const Arguments& args) override;
  std::string name() const override;
};

using Command = std::shared_ptr<CommandInterface>;

}  // namespace command
}  // namespace bash