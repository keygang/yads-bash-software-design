#include <gtest/gtest.h>

#include <parsing/parser.hpp>

namespace bash {
namespace parsing {

TEST(SplitCommands, splitCorrectly) {
  {
    std::string line = "a | b";
    std::vector<std::string> expected = {"a ", " b"};
    EXPECT_EQ(splitCommands(line), expected);
  }
  {
    std::string line = "a \"| b\"";
    std::vector<std::string> expected = {"a \"| b\""};
    EXPECT_EQ(splitCommands(line), expected);
  }
}

}  // namespace parsing
}  // namespace bash
