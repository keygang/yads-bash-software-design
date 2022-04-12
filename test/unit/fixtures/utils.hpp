#include <string>
#include <utils/filesystem.hpp>

namespace bash {
namespace test {

inline std::string getFilePath(const std::string& file_name) {
  return (fs::path(FIXTURES_FOLDER) / "files" / file_name).string();
}

}  // namespace test
}  // namespace bash