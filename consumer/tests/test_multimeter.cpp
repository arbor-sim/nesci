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

#include "catch/catch.hpp"

#include "nesci/consumer/multimeter.hpp"
#include "nesci/testing/data.hpp"

SCENARIO("consumer::Multimeter lists attributes for a timestep",
         "[nesci][nesci::consumer][nesci::consumer::Multimeter]") {
  GIVEN("a multimeter providing access to some data") {
    nesci::consumer::Multimeter multimeter(nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("attributes are requested") {
      auto attributes{
          multimeter.GetAttributes(nesci::testing::ANY_TIME_STRING)};
      THEN("the multimeter provides the attributes") {
        REQUIRE(attributes == nesci::testing::ANY_ATTRIBUTES);
      }
    }

    WHEN("attributes are requested for an invalid timestep") {
      auto attributes{multimeter.GetAttributes(nesci::testing::NO_TIME_STRING)};
      THEN("the multimeter does not provide attributes") {
        REQUIRE(attributes.empty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    nesci::consumer::Multimeter multimeter(
        nesci::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("attributes are requested") {
      auto attributes{
          multimeter.GetAttributes(nesci::testing::ANY_TIME_STRING)};
      THEN("the multimeter does not provide attributes") {
        REQUIRE(attributes.empty());
      }
    }
  }
}

SCENARIO(
    "Multimeter lists the neuron ids stored for an attribute in a "
    "timestep",
    "[nesci][nesci::consumer][nesci::consumer::Multimeter]") {
  GIVEN("a multimeter providing access to some data") {
    nesci::consumer::Multimeter multimeter(nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(nesci::testing::ANY_TIME_STRING,
                                       nesci::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter provides the ids") {
        REQUIRE(ids == nesci::testing::ANY_IDS_STRING);
      }
    }

    WHEN("neuron ids are requested for an invalid timestep") {
      auto ids{multimeter.GetNeuronIds(nesci::testing::NO_TIME_STRING,
                                       nesci::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }

    WHEN("neuron ids are requested for an invalid attribute") {
      auto ids{multimeter.GetNeuronIds(nesci::testing::ANY_TIME_STRING,
                                       nesci::testing::NO_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    nesci::consumer::Multimeter multimeter(
        nesci::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("neuron ids are requested") {
      auto ids{multimeter.GetNeuronIds(nesci::testing::ANY_TIME_STRING,
                                       nesci::testing::ANY_ATTRIBUTE)};
      THEN("the multimeter does not provide ids") { REQUIRE(ids.empty()); }
    }
  }
}
