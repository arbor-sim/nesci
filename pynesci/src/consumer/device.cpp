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

#include <string>

#include "nesci/consumer/device.hpp"
#include "pyconsumer.hpp"
#include "pynesci/suppress_warnings.hpp"

namespace pynesci {
namespace consumer {

SUPPRESS_WARNINGS_BEGIN
boost::python::list GetDeviceTimestamps(nesci::consumer::Device* device) {
  boost::python::list ret_val;
  for (const auto& timestamp : device->GetTimesteps()) {
    ret_val.append(timestamp);
  }
  return ret_val;
}

void SetDeviceNode(nesci::consumer::Device* device, const conduit::Node& node) {
  device->SetNode(&const_cast<conduit::Node&>(node));
}

template <>
void expose<nesci::consumer::Device>() {
  class_<nesci::consumer::Device>("Device", init<const std::string&>())
      .def("GetTimestamps", &GetDeviceTimestamps)
      .def("SetNode", &SetDeviceNode);
}

SUPPRESS_WARNINGS_END

}  // namespace consumer
}  // namespace pynesci
