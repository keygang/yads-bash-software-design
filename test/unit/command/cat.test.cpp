// TODO: fix inludes
#include "../../../src/commands/command.hpp"

#include <gtest/gtest.h>

namespace bash {
namespace command {

TEST(Cat, runCat) {
  Cat cat;
  {
    auto resp = cat.run({"/home/alina/PPO/yads-bash-software-design/cmake-build-debug_clang/src/test_file1"});
    EXPECT_EQ(resp.output, "Hello my fiend\n"
              "Hello my fiend 2");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatSpaceName) {
  Cat cat;
  {
    auto resp = cat.run({"/home/alina/PPO/yads-bash-software-design/cmake-build-debug_clang/src/test file2"});
    EXPECT_EQ(resp.output, "Space in name");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatMultipleArgs) {
  Cat cat;
  Pwd pwd;
  {
    auto resp = cat.run({"/home/alina/PPO/yads-bash-software-design/cmake-build-debug_clang/src/test file2",
                         "/home/alina/PPO/yads-bash-software-design/cmake-build-debug_clang/src/test_file1"});
    EXPECT_EQ(resp.output, "Space in name\nHello my fiend\n"
              "Hello my fiend 2");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatNoArgs) {
  Cat cat;
  {
    auto resp = cat.run({});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, 1);
  }
}

TEST(Cat, runCatNoSuchFile) {
  Cat cat;
  {
    auto resp = cat.run({"Abracadabra"});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, 1);
  }
}




}  // namespace command
}  // namespace bash
