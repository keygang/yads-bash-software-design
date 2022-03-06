#include <fmt/format.h>
#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <fstream>

namespace bash {
namespace command {

std::string createFile(const std::string& data, std::string file_name = "") {
  if (file_name.empty()) {
    file_name = "test.txt";
  }
  std::ofstream file(file_name);
  file << data;
  file.close();
  return file_name;
}

struct WcFixture : public testing::Test {
  void SetUp() override { wc = std::make_unique<Wc>(); }
  void runWc(const std::string& data, const CommandResponse& expected) {
    EXPECT_EQ(wc->run({}, data), expected);
    EXPECT_EQ(wc->run({createFile(data)}), expected);
  }

  std::unique_ptr<CommandInterface> wc;
};

TEST_F(WcFixture, runCorrectly) {
  {
    std::string data = "1";
    runWc(data, {fmt::format("\t{}\t{}\t{}", 1, 1, 1), {}, 0});
  }
  {
    std::string data = "123";
    runWc(data, {fmt::format("\t{}\t{}\t{}", 1, 1, 3), {}, 0});
  }
  {
    std::string data = "123 56";
    runWc(data, {fmt::format("\t{}\t{}\t{}", 1, 2, 6), {}, 0});
  }
  {
    std::string data = "123\n56";
    runWc(data, {fmt::format("\t{}\t{}\t{}", 2, 2, 6), {}, 0});
  }
  {
    std::string data = "123\n56\n";
    runWc(data, {fmt::format("\t{}\t{}\t{}", 3, 2, 7), {}, 0});
  }
}

}  // namespace command
}  // namespace bash
