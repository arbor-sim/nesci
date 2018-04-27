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
#include <sstream>
#include <string>
#include <vector>

#include "catch/catch.hpp"

#include "conduit/conduit.hpp"

#include "nesci/producer/arbor_multimeter.hpp"
#include "nesci/testing/data.hpp"

// SCENARIO("A multimeter records to a conduit node",
//          "[nesci][nesci::ArborMultimeter]") {
//   GIVEN("A conduit node and a multimeter") {
//     conduit::Node node;
//     nesci::producer::ArborMultimeter multimeter{
//         nesci::testing::ANY_MULTIMETER_NAME};
//     WHEN("recording data") {
//       nesci::producer::ArborMultimeter::Datum datum{
//           nesci::testing::ANY_TIME + nesci::testing::ANY_TIME_OFFSET,
//           nesci::testing::ANY_ATTRIBUTE, nesci::testing::ANY_ID,
//           nesci::testing::ANY_VALUE};
//       multimeter.Record(datum, &node);
//       THEN("the data is properly recorded") {
//         std::stringstream path;
//         path << nesci::testing::ANY_MULTIMETER_NAME << '/';
//         path << nesci::testing::ANY_TIME << '/';
//         path << nesci::testing::ANY_ATTRIBUTE << '/';
//         path << nesci::testing::ANY_ID;

//         REQUIRE(node[path.str()].as_double() ==
//                 Approx(nesci::testing::ANY_VALUE));
//       }
//       // id tag time value
//     }
//   }
// }
