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

#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "nesci/consumer/nest_multimeter.hpp"
#include "nesci/consumer/receiver.hpp"
#include "nesci/testing/data.hpp"
#include "nesci/testing/helpers.hpp"

SCENARIO("Consumer integration", "[niv][integration]") {
  GIVEN("The required objects") {
    conduit::Node node;

    nesci::consumer::Receiver receiver;
    receiver.SetNode(&node);

    nesci::consumer::NestMultimeter multimeter(
        nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&node);

    WHEN("The data producer sends data") {
      nesci::testing::Send(nesci::testing::ANY_NEST_DATA);

      WHEN("the consuming side receives") {
        receiver.Receive();

        WHEN("the multimeter queries the data") {
          std::vector<double> values_at_t0{multimeter.GetTimestepData(
              nesci::testing::ANY_TIME_STRING, nesci::testing::ANY_ATTRIBUTE)};
          std::vector<double> values_at_t1{
              multimeter.GetTimestepData(nesci::testing::ANOTHER_TIME_STRING,
                                         nesci::testing::ANY_ATTRIBUTE)};

          THEN("the received values are correct") {
            const std::vector<double> expected_at_t0{
                nesci::testing::ValueAt(nesci::testing::ANY_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::ANY_ID_INDEX),
                nesci::testing::ValueAt(nesci::testing::ANY_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::ANOTHER_ID_INDEX),
                nesci::testing::ValueAt(nesci::testing::ANY_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::THIRD_ID_INDEX)};
            REQUIRE(values_at_t0 == expected_at_t0);
            const std::vector<double> expected_at_t1{
                nesci::testing::ValueAt(nesci::testing::ANOTHER_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::ANY_ID_INDEX),
                nesci::testing::ValueAt(nesci::testing::ANOTHER_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::ANOTHER_ID_INDEX),
                nesci::testing::ValueAt(nesci::testing::ANOTHER_TIME_INDEX,
                                        nesci::testing::ANY_ATTRIBUTE_INDEX,
                                        nesci::testing::THIRD_ID_INDEX)};
            REQUIRE(values_at_t1 == expected_at_t1);
          }
        }
      }
    }
  }
}
