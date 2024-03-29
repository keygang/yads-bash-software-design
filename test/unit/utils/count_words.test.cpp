// TODO: fix inludes
#include <gtest/gtest.h>

#include <experimental/filesystem>
#include <utils/utils.hpp>

namespace bash {
namespace utils {

TEST(CountWords, runSimpleCount) {
  {
    std::string text = "Hello 1\n Hello2\nHello3";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 4);
  }
  {
    std::string text = "\n";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 0);
  }
  {
    std::string text = "\n\n";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 0);
  }
  {
    std::string text = "Hello world";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 2);
  }
  {
    std::string text = "Hello    world";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 2);
  }
  {
    std::string text = "Hello    world   ";
    auto resp = count_words(text);
    EXPECT_EQ(resp, 2);
  }
  {
    std::string text;
    auto resp = count_words(text);
    EXPECT_EQ(resp, 0);
  }
}

}  // namespace utils
}  // namespace bash
