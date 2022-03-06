// TODO: fix inludes
#include <gtest/gtest.h>

#include "../../../src/commands/command.hpp"

namespace bash {
namespace command {

TEST(Echo, runEcho) {
  Echo echo;
  {
    auto resp = echo.run({"hello", "world"});
    EXPECT_EQ(resp.output, "hello world");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Echo, runEchoNoArgs) {
  Echo echo;
  {
    auto resp = echo.run({});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, 0);
  }
}

}  // namespace command
}  // namespace bash
