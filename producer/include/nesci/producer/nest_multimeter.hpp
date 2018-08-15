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

#ifndef PRODUCER_INCLUDE_NESCI_PRODUCER_NEST_MULTIMETER_HPP_
#define PRODUCER_INCLUDE_NESCI_PRODUCER_NEST_MULTIMETER_HPP_

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "nesci/layout/multimeter.hpp"
#include "nesci/producer/device.hpp"

namespace nesci {
namespace producer {

class NestMultimeter final : public Device {
 public:
  struct Datum : public Device::Datum {
    using Device_t = NestMultimeter;

    Datum(double time, const std::string& neuron_id,
          const std::vector<double>& values)
        : Device::Datum{time}, neuron_id{neuron_id}, values{values} {}
    Datum(double time, std::size_t neuron_id, const std::vector<double>& values)
        : Datum{time, NestMultimeter::IdString(neuron_id), values} {}
    std::string neuron_id;
    std::vector<double> values;
  };

  NestMultimeter() = delete;
  NestMultimeter(const std::string& name,
                 const std::vector<std::string>& value_names);
  NestMultimeter(const NestMultimeter&) = default;
  NestMultimeter(NestMultimeter&&) = default;
  ~NestMultimeter() override = default;

  NestMultimeter& operator=(const NestMultimeter&) = default;
  NestMultimeter& operator=(NestMultimeter&&) = default;

  void RecordImplementation(const Datum& datum);

 private:
  static std::string IdString(std::size_t id);

  layout::Multimeter ConstructPath(const Datum& datum,
                                   std::size_t attribute_index);

  std::vector<std::string> value_names_;
};  // namespace producer

}  // namespace producer
}  // namespace nesci

#endif  // PRODUCER_INCLUDE_NESCI_PRODUCER_NEST_MULTIMETER_HPP_
