#include <gtest/gtest.h>

#include <parsing/parse_command_and_arguments.hpp>

namespace bash {
namespace parsing {

struct Substituion : public testing::Test {
  void SetUp() override {
    vars = std::make_shared<Variables>();
    parser = std::make_unique<ParseCommandAndArguments>(vars);
  }

  std::shared_ptr<Variables> vars;
  std::unique_ptr<ParseCommandAndArguments> parser;
};

TEST_F(Substituion, runCorrectly) {
  {
    (*vars)["one"] = "1";
    EXPECT_EQ(parser->substitution("$one"), "1");
    EXPECT_EQ(parser->substitution("echo $one"), "echo 1");
    EXPECT_EQ(parser->substitution("echo \"$one\""), "echo \"1\"");
    EXPECT_EQ(parser->substitution("echo \'$one\'"), "echo \'$one\'");
    EXPECT_EQ(parser->substitution("echo $one'2'"), "echo 1'2'");
  }
  {
    (*vars)["a"] = "ec";
    (*vars)["b"] = "ho";
    EXPECT_EQ(parser->substitution("$a$b hello world"), "echo hello world");
  }
}

}  // namespace parsing
}  // namespace bash
