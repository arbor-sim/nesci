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
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit_node.hpp"

#include "nesci/producer/nest_multimeter.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("A multimeter records to a conduit node",
         "[nesci][nesci::NestMultimeter]") {
  GIVEN("A conduit node and a multimeter") {
    conduit::Node node;
    nesci::producer::NestMultimeter multimeter{
        nesci::testing::ANY_MULTIMETER_NAME, nesci::testing::ANY_ATTRIBUTES,
        &node};
    WHEN("recording data") {
      nesci::producer::NestMultimeter::Datum datum{
          nesci::testing::ANY_TIME, nesci::testing::ANY_ID,
          nesci::testing::ANY_DATA_VALUES_FOR_ATTRIBUTES};
      multimeter.Record(datum);
      THEN("data is properly recorded") {
        REQUIRE(
            node[nesci::testing::PathFor(nesci::testing::ANY_MULTIMETER_NAME,
                                         nesci::testing::ANY_TIME_STRING,
                                         nesci::testing::ANY_ATTRIBUTE,
                                         nesci::testing::ANY_ID_STRING)]
                .as_double() ==
            Approx(nesci::testing::ValueAt(nesci::testing::ANY_TIME_INDEX,
                                           nesci::testing::ANY_ATTRIBUTE_INDEX,
                                           nesci::testing::ANY_ID_INDEX)));

        REQUIRE(
            node[nesci::testing::PathFor(nesci::testing::ANY_MULTIMETER_NAME,
                                         nesci::testing::ANY_TIME_STRING,
                                         nesci::testing::ANOTHER_ATTRIBUTE,
                                         nesci::testing::ANY_ID_STRING)]
                .as_double() == Approx(nesci::testing::ValueAt(
                                    nesci::testing::ANY_TIME_INDEX,
                                    nesci::testing::ANOTHER_ATTRIBUTE_INDEX,
                                    nesci::testing::ANY_ID_INDEX)));

        REQUIRE(
            node[nesci::testing::PathFor(nesci::testing::ANY_MULTIMETER_NAME,
                                         nesci::testing::ANY_TIME_STRING,
                                         nesci::testing::THIRD_ATTRIBUTE,
                                         nesci::testing::ANY_ID_STRING)]
                .as_double() == Approx(nesci::testing::ValueAt(
                                    nesci::testing::ANY_TIME_INDEX,
                                    nesci::testing::THIRD_ATTRIBUTE_INDEX,
                                    nesci::testing::ANY_ID_INDEX)));
      }
    }
  }
}
