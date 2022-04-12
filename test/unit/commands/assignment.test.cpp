#include <gtest/gtest.h>

#include <commands/command.hpp>
#include <fstream>
#include <utils/filesystem.hpp>

namespace bash {
namespace command {

struct AssignmentFixture : public testing::Test {
  std::shared_ptr<Variables> variables = std::make_shared<Variables>();
  void SetUp() override {
    assignment = std::make_unique<Assignment>(variables);
  }

  std::unique_ptr<CommandInterface> assignment;
};

TEST_F(AssignmentFixture, runAssignmentTwoArgs) {
  {
    Arguments args = {"x", "y"};
    auto resp = assignment->run(args, {});
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
    EXPECT_EQ(this->variables->at("x"), "y");
  }
}

TEST_F(AssignmentFixture, runAssignmentThreeArgs) {
  {
    Arguments args = {"x", "yz", "z"};
    auto resp = assignment->run(args, {});
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
    EXPECT_EQ(this->variables->at("x"), "yz");
    EXPECT_EQ(this->variables->size(), 1);
  }
}

TEST_F(AssignmentFixture, runAssignmentReassignment) {
  {
    Arguments args = {"x", "yz", "z"};
    auto resp = assignment->run(args, {});
    args = {"x", "z"};
    resp = assignment->run(args, {});
    EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
    EXPECT_EQ(this->variables->at("x"), "z");
    EXPECT_EQ(this->variables->size(), 1);
  }
}

TEST_F(AssignmentFixture, runAssignmentNoVar) {
  {
    Arguments args = {"", "yz", "z"};
    auto resp = assignment->run(args, {});
    EXPECT_EQ(resp.status_code, CommandStatusCode::ArgsFail);
    EXPECT_EQ(this->variables->size(), 0);
  }
}

TEST_F(AssignmentFixture, runAssignmentNoValue) {
  {
    Arguments args = {"x", "", "z"};
    auto resp = assignment->run(args, {});
    EXPECT_EQ(resp.status_code, CommandStatusCode::ArgsFail);
    EXPECT_EQ(this->variables->size(), 0);
  }
}

TEST_F(AssignmentFixture, runAssignmentMany) {
  {
    std::string var = "a";
    std::string val = "b";
    for (size_t i = 0; i < 10; ++i) {
      Arguments args = {var, val};
      auto resp = assignment->run(args, {});
      EXPECT_EQ(resp.status_code, CommandStatusCode::Ok);
      EXPECT_EQ(this->variables->at(var), val);
      EXPECT_EQ(this->variables->size(), i + 1);
      var += "a";
      val += "b";
    }
  }
}

}  // namespace command
}  // namespace bash
