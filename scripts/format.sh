#!/bin/bash

FILES=$(find ./src ./test \( -name "*.hpp" -o -name "*.cpp" \))
clang-format -i -fallback-style=none $FILES

exit 0
