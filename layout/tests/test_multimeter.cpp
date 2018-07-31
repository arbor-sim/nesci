//------------------------------------------------------------------------------
// nesci -- neural simulator conan interface
//
// Copyright (c) 2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualization Group.
//------------------------------------------------------------------------------
//                                  License
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//------------------------------------------------------------------------------

#include <string>

#include "catch/catch.hpp"

#include "nesci/layout/multimeter.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("Data layout for multimeters",
         "[nesci][nesci::layout][nesci::layout::multimeter]") {
  GIVEN("a layout for a multimeter") {
    nesci::layout::Multimeter path(nesci::testing::ANY_MULTIMETER_NAME);

    WHEN("setting a time,  an attribute, and a neuron id") {
      path.SetTime(nesci::testing::ANY_TIME_STRING);
      THEN("the multimeter reports the correct paths") {
        REQUIRE(path.GetPath() == nesci::testing::ANY_MULTIMETER_NAME +
                                      std::string("/") +
                                      nesci::testing::ANY_TIME_STRING);
      }
      WHEN("setting a time, an attribute, and a neuron id") {
        path.SetAttribute(nesci::testing::ANOTHER_ATTRIBUTE);
        THEN("the multimeter reports the correct paths") {
          REQUIRE(path.GetPath() ==
                  nesci::testing::ANY_MULTIMETER_NAME + std::string("/") +
                      nesci::testing::ANY_TIME_STRING + std::string("/") +
                      nesci::testing::ANOTHER_ATTRIBUTE);
        }
        WHEN("setting a time, an attribute, and a neuron id") {
          path.SetNeuronId(nesci::testing::THIRD_ID_STRING);
          THEN("the multimeter reports the correct paths") {
            REQUIRE(path.GetPath() ==
                    nesci::testing::ANY_MULTIMETER_NAME + std::string("/") +
                        nesci::testing::ANY_TIME_STRING + std::string("/") +
                        nesci::testing::ANOTHER_ATTRIBUTE + std::string("/") +
                        nesci::testing::THIRD_ID_STRING);
          }
        }
      }
    }
  }
}
