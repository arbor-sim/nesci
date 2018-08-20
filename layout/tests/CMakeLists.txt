#-------------------------------------------------------------------------------
# nesci -- neuronal simulator conan interface
#
# Copyright (c) 2018 RWTH Aachen University, Germany,
# Virtual Reality & Immersive Visualization Group.
#-------------------------------------------------------------------------------
#                                  License
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#-------------------------------------------------------------------------------

file(GLOB LAYOUT_TEST_SOURCES *.cpp)
file(GLOB LAYOUT_TEST_HEADERS *.hpp)

rwthvr_add_executable(
  NAME layout_tests
  SOURCES ${LAYOUT_TEST_SOURCES} 
  HEADERS ${LAYOUT_TEST_HEADERS}
  SUPPRESS_WARNINGS_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/layout_tests/suppress_warnings.hpp"
  )
  
target_include_directories(layout_tests
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include
  )
set(LAYOUT_TESTS_ARGUMENTS ""
  CACHE STRING
  "Arguments, e.g., tags, that are passed to layout_tests executable."
  )
add_test(NAME layout_tests
  COMMAND layout_tests ${LAYOUT_TESTS_ARGUMENTS}
  )

target_link_libraries(layout_tests
  PRIVATE nesci_layout
  PRIVATE testing
  PRIVATE ${CONAN_OR_CMAKE_catch}
  )
