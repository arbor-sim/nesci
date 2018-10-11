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

#include "producer_tests/suppress_warnings.hpp"
SUPPRESS_WARNINGS_BEGIN
#include "catch2/catch.hpp"
SUPPRESS_WARNINGS_END
#include "nesci/producer/producer.hpp"
#include "utilities/cout_capture.hpp"

SCENARIO("call Greet() and check output", "[producer]") {
  test_utilities::CoutCapture capture;
  nesci::producer::Greet();
  REQUIRE(capture.ToString() == "\"Hello World!\"");
}
