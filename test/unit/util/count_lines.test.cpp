// TODO: fix inludes
#include "../../../src/utils/utils.hpp"

#include <gtest/gtest.h>
#include <experimental/filesystem>



namespace bash {
namespace utils {


TEST(CountLines, runSimpleCount) {
  {
    std::string text = "Hello 1\n Hello2\nHello3";
    auto resp = count_lines(text);
    EXPECT_EQ(resp, 3);
  }
  {
    std::string text = "\n";
    auto resp = count_lines(text);
    EXPECT_EQ(resp, 2);
  }
  {
    std::string text = "\n\n";
    auto resp = count_lines(text);
    EXPECT_EQ(resp, 3);
  }
  {
    std::string text = "Hello world";
    auto resp = count_lines(text);
    EXPECT_EQ(resp, 1);
  }
  {
    std::string text;
    auto resp = count_lines(text);
    EXPECT_EQ(resp, 0);
  }
}

}  // namespace utils
}  // namespace bash
