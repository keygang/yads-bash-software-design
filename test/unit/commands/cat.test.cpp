#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <fstream>
#include <utils/filesystem.hpp>

namespace bash {
namespace command {

void create_files() {
  std::vector<std::string> filenames = {"test1", "test2", "test3"};
  std::vector<std::string> texts = {"Hello my fiend\nHello my fiend 2",
                                    "Space in name", ""};

  for (size_t i = 0; i < filenames.size(); ++i) {
    std::ofstream ostrm(filenames[i]);
    ostrm << texts[i];
    ostrm.close();
  }
}

TEST(Cat, runCat) {
  Cat cat;
  create_files();
  {
    auto work_dir = fs::current_path().string();
    auto resp = cat.run({"test1"});
    EXPECT_EQ(resp.output,
              "Hello my fiend\n"
              "Hello my fiend 2");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatSpaceName) {
  Cat cat;
  {
    auto resp = cat.run({"test2"});
    EXPECT_EQ(resp.output, "Space in name");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatMultipleArgs) {
  Cat cat;
  Pwd pwd;
  {
    auto resp = cat.run({"test2", "test1"});
    EXPECT_EQ(resp.output,
              "Space in name\nHello my fiend\n"
              "Hello my fiend 2");
    EXPECT_EQ(resp.status_code, 0);
  }
}

TEST(Cat, runCatNoArgs) {
  Cat cat;
  {
    auto resp = cat.run({});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, 1);
  }
}

TEST(Cat, runCatNoSuchFile) {
  Cat cat;
  {
    auto resp = cat.run({"Abracadabra"});
    EXPECT_EQ(resp.output, "");
    EXPECT_EQ(resp.status_code, 1);
  }
}

}  // namespace command
}  // namespace bash
