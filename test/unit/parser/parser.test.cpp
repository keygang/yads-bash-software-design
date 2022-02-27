// TODO: fix inludes
#include "../../../src/parsing/parser.hpp"

#include <gtest/gtest.h>
#include <experimental/filesystem>

namespace bash {
namespace parsing {

TEST(Parser, runParserWrongCommand) {
  Parser parser;
  {
    std::string str = "hello world";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command, nullptr);
  }
}

TEST(Parser, runParserZeroCommand) {
  Parser parser;
  {
    std::string str = "";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command, nullptr);
  }
}

TEST(Parser, runParserZeroArgs) {
  Parser parser;
  {
    std::string str = "pwd";
    auto [command, args] = parser.parse(str);
    EXPECT_EQ(command->name(), "pwd");
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
  {
    std::string str = "echo \"\"";
    auto [command, args] = parser.parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
}

TEST(Parser, runParserRightCommandInQuotes) {
  Parser parser;
  {
    std::string str = "\"echo\" hi world !";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {"hi", "world", "!"};
    EXPECT_EQ(args, right);
  }
}

TEST(Parser, runParserRightCommandNoQuotes) {
  Parser parser;
  {
    std::string str = "echo hi world !";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command->name(), "echo");
    command::Arguments right = {"hi", "world", "!"};
    EXPECT_EQ(args, right);
  }
}

TEST(Parser, runParserArgsQuotes) {
  Parser parser;
  {
    std::string str = R"(wc "test_file1" "test file2")";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command->name(), "wc");
    command::Arguments right = {"test_file1", "test file2"};
    EXPECT_EQ(args, right);
  }
}

TEST(Parser, runParserQuotes) {
  Parser parser;
  {
    std::string str = R"(wc"test_file1")";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command, nullptr);
    command::Arguments right = {};
    EXPECT_EQ(args, right);
  }
}

TEST(Parser, runParserAssignment) {
  Parser parser;
  {
    std::string str = "x=y";
    auto [command, args]= parser.parse(str);
    EXPECT_EQ(command->name(), "assignment");
    command::Arguments right = {"x", "y"};
    EXPECT_EQ(args, right);
  }
}

}  // namespace parsing
}  // namespace bash
