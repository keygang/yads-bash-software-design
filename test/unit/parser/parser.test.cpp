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

}  // namespace command
}  // namespace bash
