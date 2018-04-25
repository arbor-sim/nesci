#-------------------------------------------------------------------------------
# nesci -- neural simulator conan interface
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

set(CPPCHECK_COMMAND NOTFOUND)
find_program(CPPCHECK_COMMAND NAMES cppcheck cppcheck.exe 
    PATHS ${CONAN_BIN_DIRS_CPPCHECK} ${CONAN_BIN_DIRS_CPPCHECK_RELEASE} 
    $ENV{PATH} $ENV{CPPCHECK_DIR})

if(NOT CPPCHECK_COMMAND)
  message(SEND_ERROR
    " ERROR: Could not find cppcheck.
    Having cppcheck is a mandatory requirement.
    CMake will not generate the project without it.
    Add its location to the environments variables PATH or CPPCHECK_DIR.
	However, this should normally be supplied by conan!")
else()
  message(STATUS "Use cppcheck from: ${CPPCHECK_COMMAND}")
endif()

set(CPPCHECK_ARGUMENTS --enable=warning,performance,portability,missingInclude,unusedFunction,style --error-exitcode=1 --quiet --verbose)
if(MSVC)
  list(APPEND CPPCHECK_ARGUMENTS --template=vs)
elseif(CLANG)
  list(APPEND CPPCHECK_ARGUMENTS --template=clang)
elseif(GCC)
  list(APPEND CPPCHECK_ARGUMENTS --template=gcc)
endif()

function(ADD_TEST_CPPCHECK)
  set(options)
  set(oneValueArgs NAME)
  set(multiValueArgs)
  cmake_parse_arguments(ARGS
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
  add_test(NAME ${ARGS_NAME}
    COMMAND "${CPPCHECK_COMMAND}" ${CPPCHECK_ARGUMENTS} ${ARGS_UNPARSED_ARGUMENTS})
  set_tests_properties(${ARGS_NAME} PROPERTIES TIMEOUT 20.0)
endfunction()
