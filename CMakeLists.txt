# CMakeList.txt : CMake project for ECLTest3, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

get_property(c_known_features GLOBAL PROPERTY CMAKE_C_KNOWN_FEATURES)

project ("ECLTest3" C)

set(CMAKE_C_STANDARD 23)

# Add source to this project's executable.
add_executable (ECLTest3 "ECLTest3.c" "ECLTest3.h"
                         "Tokenizer.c" "Tokenizer.h"
                         "ECL_util.h"
                         "SquitUtil.c" "SquitUtil.h"
                         "Mapping.c"
                         "Symbols.c" "Symbols.h"
                         "StringStream.c" "StringStream.h"
                         "ArgParsing.c" "ArgParsing.h" "_RegisterWatch.h" "SquitStrings.c")

# TODO: Add tests and install targets if needed.
