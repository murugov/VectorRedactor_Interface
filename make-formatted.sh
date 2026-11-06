#!/usr/bin/env bash
# make-formatted.sh
# Using: ./make-formatted.sh

find -type f -and \( -name '*.hpp' -or -name '*.cpp' \) -exec clang-format -i {} \;
