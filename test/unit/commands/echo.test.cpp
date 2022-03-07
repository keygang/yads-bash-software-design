#include <gtest/gtest.h>

#include <commands/command.hpp>

namespace bash {
namespace command {

struct EchoFixture : public testing::Test {
  void SetUp() override { echo = std::make_unique<Echo>(); }

  std::unique_ptr<CommandInterface> echo;
};

TEST_F(EchoFixture, runEcho) {
  {
    auto resp = echo->run({"hello", "world"});
    EXPECT_EQ(resp.output, "hello world");
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
  }
}

TEST_F(EchoFixture, runEchoWithPipeArg) {
  {
    auto resp = echo->run({}, "hello world");
    EXPECT_EQ(resp.output, "hello world");
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
  }
}

TEST_F(EchoFixture, runEchoNoArgs) {
  {
    auto resp = echo->run({});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
  }
}

}  // namespace command
}  // namespace bash
