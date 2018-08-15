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

#include <string>

#include "nesci/consumer/multimeter.hpp"
#include "pyconsumer.hpp"
#include "pynesci/suppress_warnings.hpp"

namespace pynesci {
namespace consumer {

SUPPRESS_WARNINGS_BEGIN

boost::python::list GetMultimeterAttributes(
    nesci::consumer::Multimeter* multimeter, const std::string& time) {
  boost::python::list ret_val;
  for (const auto& attribute : multimeter->GetAttributes(time)) {
    ret_val.append(attribute);
  }
  return ret_val;
}

boost::python::list GetMultimeterNeuronIds(
    nesci::consumer::Multimeter* multimeter, const std::string& time,
    const std::string& attribute) {
  boost::python::list ret_val;
  for (const auto& neuron_id : multimeter->GetNeuronIds(time, attribute)) {
    ret_val.append(neuron_id);
  }
  return ret_val;
}

template <>
void expose<nesci::consumer::Multimeter>() {
  class_<nesci::consumer::Multimeter, bases<nesci::consumer::Device>>(
      "Multimeter", init<const std::string&>())
      .def("GetAttributes", &GetMultimeterAttributes)
      .def("GetNeuronIds", &GetMultimeterNeuronIds);
}

SUPPRESS_WARNINGS_END

}  // namespace consumer
}  // namespace pynesci
