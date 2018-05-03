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

#ifndef PRODUCER_INCLUDE_NESCI_PRODUCER_DEVICE_HPP_
#define PRODUCER_INCLUDE_NESCI_PRODUCER_DEVICE_HPP_

#include <string>
#include <vector>

#include "nesci/producer/suppress_warnings.hpp"

SUPPRESS_WARNINGS_BEGIN
#include "conduit/conduit_node.hpp"
SUPPRESS_WARNINGS_END

#include "nesci/layout/device.hpp"

namespace conduit {

template <>
DataArray<uint64>::~DataArray();

}  // namespace conduit

namespace nesci {
namespace producer {

class Device {
 public:
  struct Datum {
    using Device_t = Device;

    double time;
  };

  Device() = delete;
  Device(const Device&) = default;
  Device(Device&&) = default;
  virtual ~Device() = default;

  Device& operator=(const Device&) = default;
  Device& operator=(Device&&) = default;

  template <typename Datum_t>
  void Record(const Datum_t& datum);

  inline conduit::Node& node() { return node_; }
  inline const conduit::Node& node() const { return node_; }

 protected:
  explicit Device(const std::string& name);

  layout::Device ConstructPath(const Datum& datum);

  const std::string& GetName() { return name_; }

 private:
  std::string name_{""};
  conduit::Node node_;
};

template <>
inline void Device::Record(const Datum& /*datum*/) {}

template <typename Datum_t>
inline void Device::Record(const Datum_t& datum) {
  static_cast<typename Datum_t::Device_t*>(this)->Record(datum);
}

}  // namespace producer
}  // namespace nesci

#endif  // PRODUCER_INCLUDE_NESCI_PRODUCER_DEVICE_HPP_
