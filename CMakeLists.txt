# Disable in-source builds to prevent source tree corruption.
if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

cmake_minimum_required(VERSION 3.16)


project(LogicTransformer
  VERSION 1.0
  LANGUAGES CXX)

# Flags
add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
  src/logic_expression.cpp src/logic_expression.hpp
  src/valuation.cpp src/valuation.hpp
  src/variation.cpp src/variation.hpp
  src/table.cpp src/table.hpp
  src/truth_table.cpp src/truth_table.hpp
)

add_executable(logic_transformer src/main.cpp ${SOURCES})
