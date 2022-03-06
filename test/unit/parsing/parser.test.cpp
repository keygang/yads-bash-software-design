// TODO: fix inludes
#include "../../../src/parsing/parser.hpp"

#include <gtest/gtest.h>

namespace bash {
namespace parsing {

struct ParserFixture : public testing::Test {
  void SetUp() override {
    vars = std::make_shared<Variables>();
    parser = std::make_unique<Parser>(vars);
  }

  std::shared_ptr<Variables> vars;
  std::unique_ptr<ParserInterface> parser;
};

TEST_F(ParserFixture, runParserWrongCommand) {
  {
    std::string str = "hello world";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command, nullptr);
    EXPECT_TRUE(args.empty());
  }
}

TEST_F(ParserFixture, runParserZeroCommand) {
  {
    std::string str;
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command, nullptr);
    EXPECT_TRUE(args.empty());
  }
}

TEST_F(ParserFixture, runParserZeroArgs) {
  {
    std::string str = "pwd";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "pwd");
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
  {
    std::string str = "echo \"\"";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
}

TEST_F(ParserFixture, runParserRightCommandInQuotes) {
  {
    std::string str = "\"echo\" hi world !";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {"hi", "world", "!"};
    EXPECT_EQ(args, right);
  }
}

TEST_F(ParserFixture, runParserRightCommandNoQuotes) {
  {
    std::string str = "echo hi world !";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {"hi", "world", "!"};
    EXPECT_EQ(args, right);
  }
}

TEST_F(ParserFixture, runParserArgsQuotes) {
  {
    std::string str = R"(wc "test_file1" "test file2")";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "wc");
    command::Arguments right = {"test_file1", "test file2"};
    EXPECT_EQ(args, right);
  }
}

TEST_F(ParserFixture, runParserQuotes) {
  {
    std::string str = R"(wc"test_file1")";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command, nullptr);
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
}

TEST_F(ParserFixture, runParserAssignment) {
  {
    std::string str = "x=y";
    auto [command, args] = parser->parse(str);
    EXPECT_EQ(command->name(), "assignment");
    command::Arguments right = {"x", "y"};
    EXPECT_EQ(args, right);
  }
}

}  // namespace parsing
}  // namespace bash
