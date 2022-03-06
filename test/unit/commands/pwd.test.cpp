// TODO: fix inludes
#include <gtest/gtest.h>

#include "../../../src/commands/command.hpp"
#include "../../../src/utils/filesystem.hpp"

namespace bash {
namespace command {

struct PwdFixture : public testing::Test {
  void SetUp() override { pwd = std::make_unique<Pwd>(); }

  std::unique_ptr<CommandInterface> pwd;
};

TEST_F(PwdFixture, runPwd) {
  {
    auto resp = pwd->run({"hello", "world"});
    auto right_dir = fs::current_path().string();
    EXPECT_EQ(resp.output, right_dir);
    EXPECT_EQ(resp.status_code, 0);
  }

  {
    auto resp = pwd->run({}, "hello world");
    auto right_dir = fs::current_path().string();
    EXPECT_EQ(resp.output, right_dir);
    EXPECT_EQ(resp.status_code, 0);
  }

  {
    auto resp = pwd->run({});
    auto right_dir = fs::current_path().string();
    EXPECT_EQ(resp.output, right_dir);
    EXPECT_EQ(resp.status_code, 0);
  }
}

}  // namespace command
}  // namespace bash
