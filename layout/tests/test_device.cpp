//------------------------------------------------------------------------------
// nest in situ vis
//
// Copyright (c) 2017-2018 RWTH Aachen University, Germany,
// Virtual Reality & Immersive Visualisation Group.
//------------------------------------------------------------------------------
//                                 License
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

#include "nesci/layout/device.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("Data layout for devices",
         "[nesci][nesci::layout][nesci::layout::device]") {
  GIVEN("a layout for a named device") {
    nesci::layout::Device path(nesci::testing::ANY_DEVICE_NAME);

    THEN("the path for the device itself is computed correctly") {
      REQUIRE(path.GetPath() == nesci::testing::ANY_DEVICE_NAME);
    }

    WHEN("setting the time") {
      path.SetTime(nesci::testing::ANY_TIME_STRING);
      THEN("the path is computed correctly") {
        REQUIRE(path.GetPath() == nesci::testing::ANY_DEVICE_NAME +
                                      std::string("/") +
                                      nesci::testing::ANY_TIME_STRING);
      }
    }

    WHEN("setting the time") {
      path.SetTime(nesci::testing::ANY_TIME);
      THEN("the path is computed correctly") {
        REQUIRE(path.GetPath() == nesci::testing::ANY_DEVICE_NAME +
                                      std::string("/") +
                                      nesci::testing::ANY_TIME_STRING);
      }
    }
  }
}
