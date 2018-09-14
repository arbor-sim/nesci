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

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "catch2/catch.hpp"

#include "conduit/conduit.hpp"

#include "nesci/producer/arbor_multimeter.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("A arbor multimeter records to a conduit node",
         "[nesci][nesci::ArborMultimeter]") {
  GIVEN("A conduit node and a multimeter") {
    nesci::producer::ArborMultimeter multimeter{
        nesci::testing::ANY_MULTIMETER_NAME};
    WHEN("recording data") {
      nesci::producer::ArborMultimeter::Datum datum{
          nesci::testing::ANY_TIME + nesci::testing::ANY_TIME_OFFSET,
          nesci::testing::ANOTHER_ATTRIBUTE, nesci::testing::THIRD_ID_STRING,
          nesci::testing::ANY_DATA_VALUE};
      multimeter.Record(datum);
      THEN("the data is properly recorded") {
        auto node = multimeter.node();
        REQUIRE(
            node[nesci::testing::PathFor(nesci::testing::ANY_MULTIMETER_NAME,
                                         nesci::testing::ANY_TIME_STRING,
                                         nesci::testing::ANOTHER_ATTRIBUTE,
                                         nesci::testing::THIRD_ID_STRING)]
                .as_double() == Approx(nesci::testing::ANY_DATA_VALUE));
      }
    }
  }
}
