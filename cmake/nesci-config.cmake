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

get_filename_component(CURRENT_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)

foreach(COMPONENT ${nesci_FIND_COMPONENTS})
    set(COMPONENT_CONFIG_FILE ${CURRENT_DIR}/nesci_${COMPONENT}.cmake)

    if(EXISTS ${COMPONENT_CONFIG_FILE})
        include(${COMPONENT_CONFIG_FILE})
        if(NOT ${nesci_FIND_QUIETLY})
            message(STATUS "Found nesci component: ${COMPONENT}")
        endif(NOT ${nesci_FIND_QUIETLY})
    else()
        if(nesci_FIND_REQUIRED_${COMPONENT})
            set(nesci_FOUND FALSE)
        endif()

        if(NOT ${nesci_FIND_QUIETLY})
            message(STATUS "Cannot find nesci component: ${COMPONENT}")
        endif(NOT ${nesci_FIND_QUIETLY})
    endif()
endforeach()
