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

#include <string>
#include <vector>

#include "catch/Catch.hpp"

#include "nesci/consumer/arbor_multimeter.hpp"
#include "nesci/testing/data.hpp"

#include "utilities/vector_all_nan_or_empty.hpp"

SCENARIO("ArborMultimeter retrieves datum for time, attribute, neuron",
         "[niv][nesci::consumer][nesci::consumer::ArborMultimeter]") {
  GIVEN("a multimeter providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting data") {
      const double datum = multimeter.GetDatum(
          nesci::testing::ANY_TIME_STRING, nesci::testing::ANOTHER_ATTRIBUTE,
          nesci::testing::THIRD_ID_STRING);
      std::cout << "nesci::testing::ANY_TIME_STRING: "
                << nesci::testing::ANY_TIME_STRING << std::endl;
      std::cout << "nesci::testing::ANOTHER_ATTRIBUTE: "
                << nesci::testing::ANOTHER_ATTRIBUTE << std::endl;
      std::cout << "nesci::testing::THIRD_ID_STRING: "
                << nesci::testing::THIRD_ID_STRING << std::endl;

      THEN("it is correct") {
        const std::size_t DATUM_OFFSET{
            nesci::testing::ANY_TIME_OFFSET +
            nesci::testing::ANOTHER_ATTRIBUTE_OFFSET +
            nesci::testing::THIRD_ID_OFFSET};
        REQUIRE(datum == Approx(nesci::testing::ANY_DATA_VALUES[DATUM_OFFSET]));
      }
    }

    WHEN("requesting datum at an invalid time") {
      const double datum = multimeter.GetDatum(
          nesci::testing::NO_TIME_STRING, nesci::testing::ANOTHER_ATTRIBUTE,
          nesci::testing::THIRD_ID_STRING);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }

    WHEN("requesting datum for an invalid attribute") {
      const double datum = multimeter.GetDatum(nesci::testing::ANY_TIME_STRING,
                                               nesci::testing::NO_ATTRIBUTE,
                                               nesci::testing::THIRD_ID_STRING);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }

    WHEN("requesting datum for an invalid neuron id") {
      const double datum = multimeter.GetDatum(
          nesci::testing::ANY_TIME_STRING, nesci::testing::ANOTHER_ATTRIBUTE,
          nesci::testing::NO_ID_STRING);
      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting data") {
      const double datum = multimeter.GetDatum(
          nesci::testing::ANY_TIME_STRING, nesci::testing::ANOTHER_ATTRIBUTE,
          nesci::testing::THIRD_ID_STRING);

      THEN("nan is returned") { REQUIRE(std::isnan(datum)); }
    }
  }
}

SCENARIO("ArborMultimeter provides time series data",
         "[niv][nesci::consumer][nesci::consumer::ArborMultimeter]") {
  std::vector<double> expected;
  for (auto time_offset : nesci::testing::ANY_TIME_OFFSETS) {
    const auto DATUM_INDEX{time_offset +
                           nesci::testing::ANOTHER_ATTRIBUTE_OFFSET +
                           nesci::testing::THIRD_ID_OFFSET};
    expected.push_back(nesci::testing::ANY_DATA_VALUES[DATUM_INDEX]);
  }
  const std::vector<double> nans(nesci::testing::ANY_TIMES_STRING.size(),
                                 std::nan(""));

  GIVEN("a multimeter providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting time series data for an attribute and a neuron id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          nesci::testing::ANOTHER_ATTRIBUTE, nesci::testing::THIRD_ID_STRING)};

      THEN("the time series is correct") { REQUIRE(values == expected); }
    }

    WHEN(
        "requesting time series data for an invalid attribute and a neuron "
        "id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          nesci::testing::NO_ATTRIBUTE, nesci::testing::THIRD_ID_STRING)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }

    WHEN(
        "requesting time series data for an  attribute and an invalid neuron "
        "id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          nesci::testing::ANOTHER_ATTRIBUTE, nesci::testing::NO_ID_STRING)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting time series data for an attribute and a neuron id") {
      const std::vector<double> values{multimeter.GetTimeSeriesData(
          nesci::testing::ANOTHER_ATTRIBUTE, nesci::testing::THIRD_ID_STRING)};

      THEN("the time series is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }
}

SCENARIO("ArborMultimeter provides timestep data for all neurons",
         "[niv][nesci::consumer][nesci::consumer::ArborMultimeter]") {
  std::vector<double> expected;
  for (std::size_t i = 0; i < nesci::testing::ANY_IDS.size(); ++i) {
    const auto ID_OFFSET{i * nesci::testing::ID_STRIDE};
    const auto DATUM_INDEX{nesci::testing::THIRD_TIME_OFFSET +
                           nesci::testing::ANOTHER_ATTRIBUTE_OFFSET +
                           ID_OFFSET};
    expected.push_back(nesci::testing::ANY_DATA_VALUES[DATUM_INDEX]);
  }

  GIVEN("a multimeter providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::ANY_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting time step data for an attribute") {
      const std::vector<double> values{
          multimeter.GetTimestepData(nesci::testing::THIRD_TIME_STRING,
                                     nesci::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is correct") { REQUIRE(values == expected); }
    }

    WHEN("requesting time step data for an invalid time step") {
      const std::vector<double> values{multimeter.GetTimestepData(
          nesci::testing::NO_TIME_STRING, nesci::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }

    WHEN("requesting time step data for an invalid attribute") {
      const std::vector<double> values{multimeter.GetTimestepData(
          nesci::testing::THIRD_TIME_STRING, nesci::testing::NO_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }

  GIVEN("a multimeter with an incorrect name providing access to some data") {
    nesci::consumer::ArborMultimeter multimeter(
        nesci::testing::NOT_A_MULTIMETER_NAME);
    multimeter.SetNode(&nesci::testing::ANY_NEST_DATA);

    WHEN("requesting time step data for an attribute") {
      const std::vector<double> values{
          multimeter.GetTimestepData(nesci::testing::THIRD_TIME_STRING,
                                     nesci::testing::ANOTHER_ATTRIBUTE)};

      THEN("the time step data is all nans or empty") {
        REQUIRE_THAT(values, VectorAllNanOrEmpty());
      }
    }
  }
}
