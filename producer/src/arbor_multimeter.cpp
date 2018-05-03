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

#include <cmath>

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

#include "nesci/layout/multimeter.hpp"
#include "nesci/producer/arbor_multimeter.hpp"

namespace nesci {
namespace producer {

ArborMultimeter::ArborMultimeter(const std::string& name) : Device{name} {}

void ArborMultimeter::Record(const ArborMultimeter::Datum& datum) {
  const layout::Multimeter path{ConstructPath(datum)};
  node().fetch(path.GetPath()) = datum.value;
}

layout::Multimeter ArborMultimeter::ConstructPath(
    const ArborMultimeter::Datum& datum) {
  layout::Multimeter path{Device::ConstructPath(datum)};
  path.SetAttribute(datum.attribute);
  path.SetNeuronId(datum.id);
  return path;
}

}  // namespace producer
}  // namespace nesci
