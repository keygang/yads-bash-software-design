#include <gtest/gtest.h>

#include <commands/command.hpp>

namespace bash {
namespace command {

TEST(Exit, runCorrectly) {
  Exit exit;
  {
    auto response = exit.run({}, {});
    EXPECT_EQ(response.status_code, CommandStatusCode::Exit);
  }
  {
    auto response = exit.run({}, "world");
    EXPECT_EQ(response.status_code, CommandStatusCode::Exit);
  }
  {
    auto response = exit.run({"hello"}, {});
    EXPECT_EQ(response.status_code, CommandStatusCode::Exit);
  }
  {
    auto response = exit.run({"hello"}, "world");
    EXPECT_EQ(response.status_code, CommandStatusCode::Exit);
  }
}

}  // namespace command
}  // namespace bash