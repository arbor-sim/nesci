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

function(get_target_include_directories VAR)
  set(options)
  set(oneValueArgs TARGET)
  set(multiValueArgs)
  cmake_parse_arguments(ARGS
    "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if (TARGET ${ARGS_TARGET})
    # message("${ARGS_TARGET}")
    get_target_property(IS_IMPORTED ${ARGS_TARGET} IMPORTED)
    # message("imported: ${IS_IMPORTED}")
    if (${IS_IMPORTED})
      # get_target_property(INCLUDE_DIRECTORIES ${ARGS_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
    else (${IS_IMPORTED})
      get_target_property(INCLUDE_DIRECTORIES ${ARGS_TARGET} INCLUDE_DIRECTORIES)
      get_target_property(LINK_LIBRARIES ${ARGS_TARGET} LINK_LIBRARIES)

      foreach(LIB ${LINK_LIBRARIES})
        get_target_include_directories(LIB_INCLUDE_DIRECTORIES TARGET ${LIB})
        set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} ${LIB_INCLUDE_DIRECTORIES})
      endforeach(LIB ${LINK_LIBRARIES})
    endif(${IS_IMPORTED})

  else (TARGET ${ARGS_TARGET})
    set(INCLUDE_DIRECTORIES "")
  endif (TARGET ${ARGS_TARGET})

  set(${VAR} ${INCLUDE_DIRECTORIES} PARENT_SCOPE)

endfunction(get_target_include_directories)