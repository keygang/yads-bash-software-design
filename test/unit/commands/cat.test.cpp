#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <fstream>
#include <utils/filesystem.hpp>

namespace bash {
namespace command {

struct CatFixture : public testing::Test {
  void SetUp() override { cat = std::make_unique<Cat>(); }

  std::unique_ptr<CommandInterface> cat;
};

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

TEST_F(CatFixture, runCat) {
  create_files();
  {
    auto work_dir = fs::current_path().string();
    auto resp = cat->run({"test1"});
    EXPECT_EQ(resp.output,
              "Hello my fiend\n"
              "Hello my fiend 2");
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
  }
}

TEST_F(CatFixture, runCatSpaceName) {
  {
    auto resp = cat->run({"test2"});
    EXPECT_EQ(resp.output, "Space in name");
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
  }
}

TEST_F(CatFixture, runCatNoArgs) {
  {
    auto resp = cat->run({});
    EXPECT_EQ(resp.output, std::nullopt);
    EXPECT_TRUE(resp.err);
    EXPECT_EQ(resp.status_code, CommandStatusCode::ArgsFail);
  }
}

TEST_F(CatFixture, runCatNoSuchFile) {
  {
    auto resp = cat->run({"Abracadabra"});
    EXPECT_EQ(resp.output, std::nullopt);
    EXPECT_TRUE(resp.err);
    EXPECT_EQ(resp.status_code, CommandStatusCode::ArgsFail);
  }
}

}  // namespace command
}  // namespace bash
