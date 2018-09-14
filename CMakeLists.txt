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

cmake_minimum_required(VERSION 3.6.0)

project(nesci)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)

if (MSVC)
  foreach(flag_var
          CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
          CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if(${flag_var} MATCHES "/MD")
          string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
      endif(${flag_var} MATCHES "/MD")
  endforeach(flag_var)
endif (MSVC)

if(UNIX AND NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(ConanHelpers)
include(CTest)
include(GenerateExportHeader)
include(rwthvr)
include(get_target_include_directories)

enable_testing()

conan_find_package(catch2_target Catch2)
if(NOT catch2_target)
  find_package(Catch2 REQUIRED)
  set(catch2_target Catch2::Catch2)
endif()

conan_find_package(conduit_target conduit)
if(NOT conduit_target)
  find_package(conduit REQUIRED)
  set(conduit_target conduit)
endif()

conan_find_package(cpplint_target cpplint)
if (NOT cpplint_target)
  find_package(cpplint QUIET)
  if(cpplint_FOUND)
    set(cpplint_target cpplint)
  endif()
endif()
if (NOT cpplint_target)
  message(WARNING "cpplint package not found: disabling cpplint tests")
else()
  include(cpplint)
endif()

conan_find_package(cppcheck_target cppcheck)
include(cppcheck)

find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)

include(py.test)
include(python_module)

conan_find_package(boost_python_target boost_python)
if (NOT boost_python_target)
  find_package(Boost REQUIRED COMPONENTS python)
  set(boost_python_target Boost::python)
endif()

add_subdirectory(testing)
add_subdirectory(consumer)
add_subdirectory(producer)
add_subdirectory(layout)
add_subdirectory(pynesci)

get_property(ALL_SOURCES GLOBAL PROPERTY RWTHVR_ALL_SOURCES)
get_property(ALL_HEADERS GLOBAL PROPERTY RWTHVR_ALL_HEADERS)
get_property(ALL_TARGETS GLOBAL PROPERTY RWTHVR_ALL_TARGETS)

if (cpplint_target)
  add_test_cpplint(NAME "nesci-tests--cpplint"
    ${ALL_SOURCES} ${ALL_HEADERS}
  )
endif()

foreach(TARGET ${ALL_TARGETS})
  message(${TARGET})
  get_target_include_directories(TARGET_INCLUDE_DIRECTORIES TARGET ${TARGET})
  set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES};${TARGET_INCLUDE_DIRECTORIES})
endforeach(TARGET ${ALL_TARGETS})
list(REMOVE_DUPLICATES INCLUDE_DIRECTORIES)

add_test_cppcheck(NAME "nesci-tests--cppcheck"
  SOURCES ${ALL_SOURCES}
  INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES}
)

install(
  FILES ${CMAKE_SOURCE_DIR}/cmake/nesci-config.cmake
  DESTINATION lib/nesci/cmake)
