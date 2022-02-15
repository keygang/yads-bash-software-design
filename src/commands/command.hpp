#pragma once

#include "arguments.hpp"

namespace bash {
namespace command {

struct CommandResponse {
  std::string output;
  int status_code;
};

class Command {
public:
  virtual CommandResponse run(const Arguments& args) = 0;
};

class Echo : public Command{
public:
  CommandResponse run(const Arguments& args) override;
};

}
}