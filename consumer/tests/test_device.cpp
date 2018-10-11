//------------------------------------------------------------------------------
// nesci -- neuronal simulator conan interface
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
#include <vector>

#include "catch2/catch.hpp"

#include "nesci/consumer/device.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("consumer::Device lists the timesteps",
         "[nesci][nesci::consumer][nesci::consumer::Device]") {
  GIVEN("a device providing access to some data") {
    nesci::consumer::Device device(nesci::testing::ANY_DEVICE_NAME);
    device.SetNode(&nesci::testing::ANY_NEST_DATA);

    THEN("the device provides correct timesteps as strings") {
      REQUIRE(device.GetTimesteps() == nesci::testing::ANY_TIMES_STRING);
    }
  }

  GIVEN("a device with an incorrect name providing access to some data") {
    nesci::consumer::Device multimeter(nesci::testing::NOT_A_DEVICE_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    THEN("the device does not provide timesteps as strings") {
      REQUIRE(multimeter.GetTimesteps().empty());
    }
    THEN("the device does not provide timesteps as doubles") {
      REQUIRE(multimeter.GetTimesteps().empty());
    }
  }
}
