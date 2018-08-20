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

#include "nesci/consumer/arbor_multimeter.hpp"
#include "pyconsumer.hpp"
#include "pynesci/suppress_warnings.hpp"

namespace pynesci {
namespace consumer {

SUPPRESS_WARNINGS_BEGIN

boost::python::list GetArborMultimeterTimestepData(
    nesci::consumer::ArborMultimeter* arbor_multimeter, const std::string& time,
    const std::string& attribute) {
  boost::python::list ret_val;
  for (const auto& data : arbor_multimeter->GetTimestepData(time, attribute)) {
    ret_val.append(data);
  }
  return ret_val;
}

boost::python::list GetArborTimeSeriesData(
    nesci::consumer::ArborMultimeter* arbor_multimeter,
    const std::string& attribute, const std::string& neuron_id) {
  boost::python::list ret_val;
  for (const auto& data :
       arbor_multimeter->GetTimeSeriesData(attribute, neuron_id)) {
    ret_val.append(data);
  }
  return ret_val;
}

template <>
void expose<nesci::consumer::ArborMultimeter>() {
  class_<nesci::consumer::ArborMultimeter, bases<nesci::consumer::Multimeter>>(
      "ArborMultimeter", init<const std::string&>())
      .def("GetTimestepData", &GetArborMultimeterTimestepData)
      .def("GetTimeSeriesData", &GetArborTimeSeriesData)
      .def("GetDatum", &nesci::consumer::ArborMultimeter::GetDatum);
}

SUPPRESS_WARNINGS_END

}  // namespace consumer
}  // namespace pynesci
