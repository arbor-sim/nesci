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

#ifndef TESTING_INCLUDE_NESCI_TESTING_DATA_HPP_
#define TESTING_INCLUDE_NESCI_TESTING_DATA_HPP_

#include <cmath>

#include <limits>
#include <sstream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"
#include "nesci/layout/utility.hpp"
#include "nesci/testing/conduit_schema.hpp"

#if defined(__GNUC__) && !defined(__clang__)
#define NESCI_UNUSED __attribute__((unused))
#else
#define NESCI_UNUSED
#endif

namespace nesci {
namespace testing {

class Data;

NESCI_UNUSED static const char* ANY_DEVICE_NAME{"multimeter A"};
NESCI_UNUSED static const char* NOT_A_DEVICE_NAME{"NOT_A_DEVICE_NAME"};

NESCI_UNUSED static const char* ANY_MULTIMETER_NAME{"multimeter A"};
NESCI_UNUSED static const char* NOT_A_MULTIMETER_NAME{"NOT_A_MULTIMETER_NAME"};

NESCI_UNUSED static const char* ANY_SPIKE_DETECTOR_NAME{"spikes A"};
NESCI_UNUSED static const char* NOT_A_SPIKE_DETECTOR_NAME{
    "NOT_A_SPIKE_DETECTOR_NAME"};

#define NESCI_TESTING_TRIPLET(type, name, value0, value1, value2, invalid) \
  NESCI_UNUSED static const type ANY_##name{value0};                       \
  NESCI_UNUSED static const type ANOTHER_##name{value1};                   \
  NESCI_UNUSED static const type THIRD_##name{value2};                     \
  NESCI_UNUSED static const type NO_##name { invalid }
#define NESCI_TESTING_TRIPLET_VECTOR(type, name, value0, value1, value2,    \
                                     invalid)                               \
  NESCI_UNUSED static const std::vector<type> ANY_##name##S{value0, value1, \
                                                            value2};        \
  NESCI_TESTING_TRIPLET(type, name, value0, value1, value2, invalid)
#define NESCI_TESTING_TRIPLET_VECTOR_STRING(name, value0, value1, value2) \
  NESCI_UNUSED static const std::vector<std::string> ANY_##name##S{       \
      value0, value1, value2};                                            \
  NESCI_TESTING_TRIPLET(char*, name, value0, value1, value2, "NO ##name")
#define NESCI_TESTING_TRIPLET_VECTOR_STRINGIFIED(name)                         \
  NESCI_UNUSED static const std::vector<std::string> ANY_##name##S_STRING{     \
      nesci::layout::utility::to_string(ANY_##name),                           \
      nesci::layout::utility::to_string(ANOTHER_##name),                       \
      nesci::layout::utility::to_string(THIRD_##name)};                        \
  NESCI_TESTING_TRIPLET(char*, name##_STRING, ANY_##name##S_STRING[0].c_str(), \
                        ANY_##name##S_STRING[1].c_str(),                       \
                        ANY_##name##S_STRING[2].c_str(), "NO ##name STRING")
#define NESCI_TESTING_INDEX_TRIPLET(name) \
  NESCI_TESTING_TRIPLET(std::size_t, name, 0ul, 1ul, 2ul, 3ul)

NESCI_TESTING_INDEX_TRIPLET(INDEX);
NESCI_TESTING_INDEX_TRIPLET(TIME_INDEX);
NESCI_TESTING_INDEX_TRIPLET(ATTRIBUTE_INDEX);
NESCI_TESTING_INDEX_TRIPLET(ID_INDEX);

NESCI_TESTING_TRIPLET_VECTOR(double, TIME, 0.1, 0.2, 0.3, std::nan("NO TIME"));
NESCI_TESTING_TRIPLET_VECTOR_STRINGIFIED(TIME);
NESCI_TESTING_TRIPLET_VECTOR_STRING(ATTRIBUTE, "V_m", "g_e", "g_i");
NESCI_TESTING_TRIPLET_VECTOR(std::size_t, ID, 1ul, 2ul, 3ul,
                             std::numeric_limits<std::size_t>::max());
NESCI_TESTING_TRIPLET_VECTOR_STRINGIFIED(ID);

inline std::string PathFor(const std::string& device_name,
                           const std::string& timestep,
                           const std::string& attribute,
                           const std::string& neuron_id) {
  return device_name + '/' + timestep + '/' + attribute + '/' + neuron_id;
}

// clang-format off
NESCI_UNUSED static const std::vector<double> ANY_DATA_VALUES{
  0.111, 0.112, 0.113,  0.121, 0.122, 0.123,  0.131, 0.132, 0.133,
  0.211, 0.212, 0.213,  0.221, 0.222, 0.223,  0.231, 0.232, 0.233,
  0.311, 0.312, 0.313,  0.321, 0.322, 0.323,  0.331, 0.332, 0.333};
// clang-format on
NESCI_UNUSED static const double ANY_DATA_VALUE{ANY_DATA_VALUES[0]};
NESCI_UNUSED static const std::vector<double> ANY_DATA_VALUES_FOR_ATTRIBUTES{
    ANY_DATA_VALUES[0], ANY_DATA_VALUES[3], ANY_DATA_VALUES[6]};

NESCI_UNUSED static const std::size_t TIME_STRIDE{9};
NESCI_UNUSED static const std::size_t ATTRIBUTE_STRIDE{3};
NESCI_UNUSED static const std::size_t ID_STRIDE{1};

inline double ValueAt(std::size_t time_id, std::size_t attribute_id,
                      std::size_t neuron_id) {
  const std::size_t index = time_id * TIME_STRIDE +
                            attribute_id * ATTRIBUTE_STRIDE +
                            neuron_id * ID_STRIDE;
  return ANY_DATA_VALUES[index];
}

NESCI_TESTING_TRIPLET_VECTOR(std::size_t, TIME_OFFSET,
                             ANY_INDEX* nesci::testing::TIME_STRIDE,
                             ANOTHER_INDEX* nesci::testing::TIME_STRIDE,
                             THIRD_INDEX* nesci::testing::TIME_STRIDE,
                             std::numeric_limits<std::size_t>::max());
NESCI_TESTING_TRIPLET_VECTOR(std::size_t, ATTRIBUTE_OFFSET,
                             ANY_INDEX* nesci::testing::ATTRIBUTE_STRIDE,
                             ANOTHER_INDEX* nesci::testing::ATTRIBUTE_STRIDE,
                             THIRD_INDEX* nesci::testing::ATTRIBUTE_STRIDE,
                             std::numeric_limits<std::size_t>::max());
NESCI_TESTING_TRIPLET_VECTOR(std::size_t, ID_OFFSET,
                             ANY_INDEX* nesci::testing::ID_STRIDE,
                             ANOTHER_INDEX* nesci::testing::ID_STRIDE,
                             THIRD_INDEX* nesci::testing::ID_STRIDE,
                             std::numeric_limits<std::size_t>::max());

inline static const std::string AnyNestDataSchema() {
  std::stringstream s;
  std::size_t offset = 0;
  const std::size_t datum_size = 8;
  s << "{\n";
  s << "  " << conduit_schema::OpenTag(ANY_MULTIMETER_NAME);
  for (auto time : ANY_TIMES) {
    s << "    "
      << conduit_schema::OpenTag(nesci::layout::utility::to_string(time));
    for (auto attribute : ANY_ATTRIBUTES) {
      s << "      " << conduit_schema::OpenTag(attribute);
      for (auto id : ANY_IDS) {
        s << "        "
          << conduit_schema::OpenTag(nesci::layout::utility::to_string(id));
        s << "          "
          << conduit_schema::DoubleData((offset++) * datum_size);
        s << "        " << conduit_schema::CloseTagNext();
      }
      conduit_schema::RemoveNextIndicator(&s);
      s << "      " << conduit_schema::CloseTagNext();
    }
    conduit_schema::RemoveNextIndicator(&s);
    s << "    " << conduit_schema::CloseTagNext();
  }
  conduit_schema::RemoveNextIndicator(&s);
  s << "  " << conduit_schema::CloseTag();
  s << "}";
  return s.str();
}

NESCI_UNUSED static conduit::Node ANY_NEST_DATA{
    AnyNestDataSchema(), const_cast<double*>(ANY_DATA_VALUES.data()), false};

}  // namespace testing
}  // namespace nesci

#endif  // TESTING_INCLUDE_NESCI_TESTING_DATA_HPP_
