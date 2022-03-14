#include <fmt/format.h>
#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <iostream>
#include <unit/fixtures/utils.hpp>

namespace bash {
namespace command {

struct ExternalFixture : public testing::Test {
  void SetUp() override { variables = std::make_shared<Variables>(); }

  void runExternal(const std::string& file_name,
                   const CommandResponse& expected) const {
    auto external = ExternalCommand(file_name, variables);
    auto response = external.run({}, {});
    EXPECT_EQ(response, expected);
  }

  std::shared_ptr<Variables> variables;
};

TEST_F(ExternalFixture, runEchoCorrectly) {
  {
    std::string file_name = fmt::format("{}", test::getFilePath("echo.sh"));
    runExternal(file_name, {"Hello World\n", {}, CommandStatusCode::Ok});
  }
}

}  // namespace command
}  // namespace bash
