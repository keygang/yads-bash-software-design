#pragma once

#if (defined(__GNUC__) && __GNUC__ > 8) || \
    (defined(__clang_major__) && __clang_major__ > 8)

#include <filesystem>
namespace fs = std::filesystem;

#else

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

#endif
