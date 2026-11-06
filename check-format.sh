#!/usr/bin/env bash
# check-format.sh
# Using: ./check-format.sh

find -type f -and \( -name '*.hpp' -or -name '*.cpp' \) -exec clang-format --dry-run {} \;
