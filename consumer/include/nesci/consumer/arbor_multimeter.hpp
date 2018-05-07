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

#ifndef CONSUMER_INCLUDE_NESCI_CONSUMER_ARBOR_MULTIMETER_HPP_
#define CONSUMER_INCLUDE_NESCI_CONSUMER_ARBOR_MULTIMETER_HPP_

#include <string>
#include <vector>

#include "nesci/consumer/multimeter.hpp"
#include "nesci/layout/multimeter.hpp"

namespace nesci {
namespace consumer {

class ArborMultimeter : public nesci::consumer::Multimeter {
 public:
  ArborMultimeter() = delete;
  explicit ArborMultimeter(const std::string& name);
  ArborMultimeter(const ArborMultimeter&) = default;
  ArborMultimeter(ArborMultimeter&&) = default;
  ~ArborMultimeter() = default;

  ArborMultimeter& operator=(const ArborMultimeter&) = default;
  ArborMultimeter& operator=(ArborMultimeter&&) = default;

  std::vector<double> GetTimestepData(const std::string& time,
                                      const std::string& attribute) const;

  std::vector<double> GetTimeSeriesData(const std::string& attribute,
                                        const std::string& neuron_id) const;

  double GetDatum(const std::string& time, const std::string& attribute,
                  const std::string& neuron_id) const;
};

}  // namespace consumer
}  // namespace nesci

#endif  // CONSUMER_INCLUDE_NESCI_CONSUMER_ARBOR_MULTIMETER_HPP_
