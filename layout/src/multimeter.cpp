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

#include "nesci/layout/multimeter.hpp"

#include <string>

namespace nesci {
namespace layout {

Multimeter::Multimeter(const std::string& name) : Device(name) {}

Multimeter::Multimeter(const Device& device) : Device(device) {}

Multimeter::Multimeter(Device&& device) : Device(device) {}

std::string Multimeter::GetPath() const {
  return Device::GetPath() + SuffixIfNotEmpty(attribute_) +
         SuffixIfNotEmpty(neuron_id_);
}

void Multimeter::SetAttribute(const std::string& attribute) {
  attribute_ = attribute;
}

void Multimeter::SetNeuronId(const std::string& neuron_id) {
  neuron_id_ = neuron_id;
}

}  // namespace layout
}  // namespace nesci
