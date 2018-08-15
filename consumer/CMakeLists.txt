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

file(GLOB CONSUMER_SOURCES src/*.cpp)
file(GLOB CONSUMER_HEADERS include/nesci/consumer/*.hpp)

rwthvr_add_library(NAME nesci_consumer
  SOURCES ${CONSUMER_SOURCES}
  HEADERS ${CONSUMER_HEADERS}
  SUPPRESS_WARNINGS_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/consumer/suppress_warnings.hpp"
  )
generate_export_header(nesci_consumer
  EXPORT_FILE_NAME
  "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/consumer/export.hpp"
  )
  
target_include_directories(nesci_consumer
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
  PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include
  )

target_link_libraries(nesci_consumer
  PUBLIC nesci_layout
  PUBLIC ${CONAN_OR_CMAKE_conduit}
  )

target_compile_options(nesci_consumer
  PRIVATE -fPIC
  )

add_subdirectory(tests)
