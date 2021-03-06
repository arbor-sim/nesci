//------------------------------------------------------------------------------
// nesci -- neuronal simulator conan interface
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

#include "catch2/catch.hpp"

#include "nesci/layout/spike_detector.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("Data layout for spike detectors",
         "[nesci][nesci::layout][nesci::layout::SpikeDetector]") {
  GIVEN("a layout for a multimeter") {
    nesci::layout::SpikeDetector path(nesci::testing::ANY_SPIKE_DETECTOR_NAME);

    WHEN("setting a time") {
      path.SetTime(nesci::testing::ANY_TIME_STRING);
      THEN("the spike detector reports the correct paths") {
        REQUIRE(path.GetPath() == nesci::testing::ANY_SPIKE_DETECTOR_NAME +
                                      std::string("/") +
                                      nesci::testing::ANY_TIME_STRING);
      }
    }
  }
}
