// TODO: fix inludes
#include "../../../src/commands/command.hpp"

#include <gtest/gtest.h>

namespace bash {
namespace command {

TEST(Echo, runEcho) {
  Echo echo;
  {
    auto resp = echo.run({"hello", "world"});
    EXPECT_EQ(resp.output, "hello world");
    EXPECT_EQ(resp.status_code, 0);
  }

  {
    auto resp = echo.run({"L l"});
    EXPECT_EQ(resp.output, "L l");
    EXPECT_EQ(resp.status_code, 0);
  }

}

}  // namespace command
}  // namespace bash
