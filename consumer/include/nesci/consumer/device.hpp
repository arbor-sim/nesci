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

#ifndef CONSUMER_INCLUDE_NESCI_CONSUMER_DEVICE_HPP_
#define CONSUMER_INCLUDE_NESCI_CONSUMER_DEVICE_HPP_

#include <string>
#include <vector>

#include "conduit/conduit_node.hpp"

namespace nesci {
namespace consumer {

class Device {
 public:
  Device() = delete;
  explicit Device(const std::string& name);
  Device(const Device&) = default;
  Device(Device&&) = default;
  virtual ~Device() = default;

  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) = default;

  std::vector<std::string> GetTimestepsString() const;
  const std::vector<double> GetTimesteps() const;

  void SetNode(const conduit::Node* node) { node_ = node; }

 protected:
  std::vector<std::string> GetChildNames(const std::string& path) const;

  const conduit::Node* GetNode(const std::string& path) const;

  std::string ConstructPath() const;
  std::string ConstructPath(const std::string& time) const;

 private:
  const conduit::Node* node_{nullptr};
  std::string name_{""};
};

}  // namespace consumer
}  // namespace nesci

#endif  // CONSUMER_INCLUDE_NESCI_CONSUMER_DEVICE_HPP_
