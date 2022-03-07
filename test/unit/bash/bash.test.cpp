#include <gtest/gtest.h>

#include <bash/bash.hpp>

namespace bash {

struct BashFixture : testing::Test {
  void SetUp() override { bash = std::make_unique<Bash>(stream); }

  std::stringstream stream;
  std::unique_ptr<Bash> bash;
};

TEST_F(BashFixture, simpleExitCorrectly) {
  stream << "exit";
  bash->run();
  EXPECT_TRUE(true);
}

TEST_F(BashFixture, concatedExitCorrectly) {
  stream << "a=ex\n";
  stream << "b=it\n";
  stream << "$a$b\n";
  bash->run();
  EXPECT_TRUE(true);
}

}  // namespace bash
