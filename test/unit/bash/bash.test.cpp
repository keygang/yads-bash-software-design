#include <gtest/gtest.h>

#include <bash/bash.hpp>

namespace bash {

struct BashFixture : testing::Test {
  void SetUp() override { bash = std::make_unique<Bash>(in_stream, out, err); }

  std::stringstream in_stream;
  std::ostringstream out;
  std::ostringstream err;
  std::unique_ptr<Bash> bash;
};

TEST_F(BashFixture, simpleExitCorrectly) {
  in_stream << "exit";
  bash->run();
  EXPECT_TRUE(true);
}

TEST_F(BashFixture, concatedExitCorrectly) {
  in_stream << "a=ex\n";
  in_stream << "b=it\n";
  in_stream << "$a$b\n";
  bash->run();
  EXPECT_TRUE(true);
}

}  // namespace bash
