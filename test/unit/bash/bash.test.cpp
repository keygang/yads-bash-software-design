#include <gtest/gtest.h>

#include <bash/bash.hpp>

namespace bash {

struct BashFixture : testing::Test {
  void SetUp() override {
    Config config;
    config.in_stream = &in_stream;
    config.out_stream = &out_stream;
    config.err_stream = &err_stream;
    config.show_hint = false;

    bash = std::make_unique<Bash>(config);
  }

  std::stringstream in_stream;
  std::stringstream out_stream;
  std::stringstream err_stream;
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

TEST_F(BashFixture, substitutionInEcho) {
  in_stream << "one=1\n";
  in_stream << "echo $one'2'\n";
  in_stream << "exit";
  bash->run();
  std::string result;
  EXPECT_EQ(out_stream.str(), "12\n");
}

TEST_F(BashFixture, PipelileSimple1) {
  in_stream << "echo 123 | wc\n";
  in_stream << "exit";
  bash->run();
  std::string result;
  EXPECT_EQ(out_stream.str(), "\t1\t1\t3\n");
}

TEST_F(BashFixture, PipelileSimple2) {
  in_stream << "echo 123 | echo hi\n";
  in_stream << "exit";
  bash->run();
  std::string result;
  EXPECT_EQ(out_stream.str(), "123\n");
}

TEST_F(BashFixture, PipelileSimple3) {
  in_stream << "echo 123 | wc | echo | wc\n";
  in_stream << "exit";
  bash->run();
  std::string result;
  EXPECT_EQ(out_stream.str(), "\t1\t3\t6\n");
}

}  // namespace bash
