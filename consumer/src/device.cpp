//------------------------------------------------------------------------------
// nest in situ vis
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

#include "nesci/consumer/device.hpp"

#include <cmath>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "nesci/layout/device.hpp"
#include "nesci/layout/suppress_warnings.hpp"

namespace nesci {
namespace consumer {

Device::Device(const std::string& name) : name_{name} {}

std::vector<std::string> Device::GetTimesteps() const {
  layout::Device path(name_);
  std::vector<std::string> retvec;
  for (auto s : GetChildNames(path)) {
    std::stringstream ss;
    ss.precision(5);
    ss << std::fixed << std::stod(s);
    retvec.push_back(ss.str());
  }
  return retvec;
}

std::string Device::GetName() const { return name_; }

std::vector<std::string> Device::GetChildNames(
    const layout::Device& path) const {
  const conduit::Node* node{GetNode(path)};
  return (node != nullptr) ? node->child_names() : std::vector<std::string>();
}

double Device::GetValue(const layout::Device& path) const {
  const conduit::Node* node{GetNode(path)};
  return (node != nullptr) ? node->as_double() : std::nan("");
}

std::vector<std::uint64_t> Device::GetUint64Values(
    const layout::Device& path) const {
  const conduit::Node* node{GetNode(path)};
  if (node != nullptr) {
    SUPPRESS_WARNINGS_BEGIN
    const auto data_array = node->as_uint64_array();
    SUPPRESS_WARNINGS_END
    return std::vector<std::uint64_t>{
        &data_array[0], &data_array[0] + data_array.number_of_elements()};
  } else {
    return std::vector<std::uint64_t>{};
  }
}

const conduit::Node* Device::GetNode(const layout::Device& path) const {
  const conduit::Node* node{nullptr};
  try {
    node = &(node_->fetch_child(path.GetPath()));
  } catch (...) {
  }
  return node;
}

}  // namespace consumer
}  // namespace nesci
