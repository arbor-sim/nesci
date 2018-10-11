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

file(GLOB LAYOUT_SOURCES src/*.cpp)
file(GLOB LAYOUT_HEADERS include/nesci/layout/*.hpp)

rwthvr_add_library(NAME nesci_layout
  SOURCES ${LAYOUT_SOURCES}
  HEADERS ${LAYOUT_HEADERS}
  SUPPRESS_WARNINGS_HEADER "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/layout/suppress_warnings.hpp"
  )
generate_export_header(nesci_layout
  EXPORT_FILE_NAME
  "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/layout/export.hpp"
  )

target_include_directories(nesci_layout PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_options(nesci_layout
  PRIVATE -fPIC
  )

install(
  TARGETS nesci_layout
  EXPORT nesci_layout
  ARCHIVE DESTINATION lib
  COMPONENT zmq)

install(
  EXPORT nesci_layout
  DESTINATION lib/nesci/cmake)

install(
  FILES ${LAYOUT_HEADERS} "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/layout/export.hpp" "${CMAKE_CURRENT_BINARY_DIR}/include/nesci/layout/suppress_warnings.hpp"
  DESTINATION "include/nesci/layout")

add_subdirectory(tests)
