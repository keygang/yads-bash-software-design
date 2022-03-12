#include <fmt/format.h>
#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <fstream>

namespace bash {
namespace command {

std::string createFileExe(const std::string& data, std::string file_name = "") {
  if (file_name.empty()) {
    file_name = "test.sh";
  }
  std::ofstream file(file_name);
  file << data;
  file.close();
  return file_name;
}

struct ExternalFixture : public testing::Test {
  std::shared_ptr<Variables> variables = std::make_shared<Variables>();
  void runExternal(const std::string& data, const CommandResponse& expected) {
    createFileExe(data, "external.sh");
    external = std::make_unique<ExternalCommand>("/external.sh", variables);
    auto resp = external->run({}, {});
    EXPECT_EQ(external->run({}, data), expected);
    //EXPECT_EQ(external->run({createFileExe(data)}), expected);
  }

  std::unique_ptr<CommandInterface> external;

};

TEST_F(ExternalFixture, runCorrectly) {
  {
    std::string data = "#!/bin/bash\n"
        "echo \"Hello World\"";
    runExternal(data,
          {fmt::format("\t{}\t{}\t{}", 1, 1, 1), {}, CommandStatusCode::Ok});
  }

}

}  // namespace command
}  // namespace bash
