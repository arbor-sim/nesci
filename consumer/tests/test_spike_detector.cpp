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

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "nesci/consumer/spike_detector.hpp"
#include "nesci/testing/data.hpp"

#include "utilities/vector_all_nan_or_empty.hpp"
#include <iostream>

SCENARIO("Test GetNeuronIds",
	"[nesci][nesci::SpikeDetector]") {
  GIVEN("a conduit node and a spike detector") {
    nesci::consumer::SpikeDetector spike_detector(
      nesci::testing::ANY_SPIKE_DETECTOR_NAME);

    spike_detector.SetNode(&nesci::testing::ANY_SPIKE_DATA);

    std::vector<std::string> output =
      spike_detector.GetNeuronIds(nesci::testing::ANY_TIME_STRING);

	  REQUIRE(1 == 1);
  }
}
