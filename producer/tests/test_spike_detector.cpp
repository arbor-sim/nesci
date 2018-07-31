//------------------------------------------------------------------------------
// nesci -- neural simulator conan interface
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

#include <memory>
#include <string>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "nesci/producer/spike_detector.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("A spike detector records to a conduit node",
         "[nesci][nesci::SpikeDetector]") {
  GIVEN("a conduit node and a spike detector") {
    nesci::producer::SpikeDetector spike_detector(
        nesci::testing::ANY_SPIKE_DETECTOR_NAME);

    WHEN("recording") {
      spike_detector.Record(nesci::producer::SpikeDetector::Datum{
          nesci::testing::ANY_TIME, nesci::testing::ANY_ID});
      THEN("data is recorded in the node") {
        const auto recorded_node =
            spike_detector.node()[nesci::testing::ANY_SPIKE_DETECTOR_NAME]
                                 [nesci::testing::ANY_TIME_STRING];
        REQUIRE(recorded_node.as_uint64_array()[0] == nesci::testing::ANY_ID);
      }
      WHEN("recording another spike") {
        spike_detector.Record(
            {nesci::testing::ANY_TIME, nesci::testing::ANOTHER_ID});
        THEN("data is recorded in the node") {
          const auto recorded_node =
              spike_detector.node()[nesci::testing::ANY_SPIKE_DETECTOR_NAME]
                                   [nesci::testing::ANY_TIME_STRING];
          REQUIRE(recorded_node.as_uint64_array()[0] == nesci::testing::ANY_ID);
          REQUIRE(recorded_node.as_uint64_array()[1] ==
                  nesci::testing::ANOTHER_ID);
        }
      }
    }
  }
}
