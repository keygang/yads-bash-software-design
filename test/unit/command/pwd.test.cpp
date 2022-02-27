// TODO: fix inludes
#include "../../../src/commands/command.hpp"

#include <gtest/gtest.h>
#include <experimental/filesystem>

namespace bash {
namespace command {

TEST(Pwd, runPwd) {
  Pwd pwd;
  {
    auto resp = pwd.run({"hello", "world"});
    auto right_dir = std::experimental::filesystem::current_path().string();
    EXPECT_EQ(resp.output, right_dir);
    EXPECT_EQ(resp.status_code, 0);
  }

  {
    auto resp = pwd.run({});
    auto right_dir = std::experimental::filesystem::current_path().string();
    EXPECT_EQ(resp.output, right_dir);
    EXPECT_EQ(resp.status_code, 0);
  }
}

}  // namespace command
}  // namespace bash
